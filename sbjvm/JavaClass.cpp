#include "include/JavaClass.hpp"
#include "include/AssemblyMap.hpp"

Security *verifier;

JavaClass::JavaClass(){
    // Inicialização dos atributos de JavaClass
    this->bytes = nullptr;
    this->bcSize = 0;
    this->bytecode_index = 0;

    // Inicialização dos atributos herdados de JavaClassFileFormat
    this->magic = 0;
    this->minor_version = 0;
    this->major_version = 0;
    
    this->constant_pool_count = 0;
    this->constant_pool = nullptr;

    this->access_flags = 0;
    this->this_class = 0;
    this->super_class = 0;

    this->interfaces_count = 0;
    this->interfaces = nullptr;

    this->fields_count = 0;
    this->fields = nullptr;

    this->methods_count = 0;
    this->methods = nullptr;

    this->attributes_count = 0;
    this->attributes = nullptr;

    this->classFilePath = "";
}

bool JavaClass::readClassFile(std::string className){
    std::ifstream file;
    u1 byte;
    long long int aux = 0;
    bool verifyMagic = false, verifyVersion = false;

    verifier = Security::getInstance();

    file.open(className, std::ifstream::binary);
    if (file.is_open()) {
        while(true){
            file.read((char*)&byte, 1);
            if (file.eof())
                break;

            insertByte(byte);
            aux++;

            if(aux == 4){
                setClassMagic();
                verifyMagic = verifier->verifyMagic(magic);
                if(!verifyMagic)
                    break;
            }
            if(aux == 8){
                setVersions(4);
                setVersions(6);
                verifyVersion = verifier->verifyClassVersion(minor_version, major_version);
                if(!verifyVersion)
                    break;
            }
        }

        file.close();

        if(verifyMagic){
            if(verifyVersion){
                setCPCount();
                setConstantPool();
                setClassInfo();
            } else{
                std::cout << "Invalid Java Version!\n";
                return false;
            }
        }
        else{
            std::cout << "Invalid Magic!" << std::endl;
            return false;
        }

        return true;
    } else {
        std::cout << "(E) Could not open the specified entrypoint class file: "<< className << std::endl;
        throw std::invalid_argument("ClassFileNotFound");
    }

    this->classFilePath = className;

    return false;
}

void JavaClass::deleteBytecode(){
    bytecode *p1;

    while(bytes != nullptr){
        p1 = bytes->next;
        free(bytes);
        bytes = p1;
    }
    free(bytes);
}

void JavaClass::deleteConstantPool(){
    for(u2 i = 0; i < constant_pool_count - 1; i++){
        if(constant_pool[i].tag == CONSTANT_Utf8){
            free(constant_pool[i].info.utf8Info.bytes);
        }
    }
    free(constant_pool);
}

void JavaClass::deleteClassInfo(){
    free(interfaces);

    for(u2 i = 0; i < fields_count; i++){
        if(fields[i].attributes_count > 0){
            for(u2 j = 0; j < fields[i].attributes_count; j++)
                deleteAttributes(fields[i].attributes[j]);
        }
        free(fields[i].attributes);
    }
    free(fields);

    for(u2 i = 0; i < methods_count; i++){
        if(methods[i].attributes_count > 0){
            for(u2 j = 0; j < methods[i].attributes_count; j++)
                deleteAttributes(methods[i].attributes[j]);
        }
        free(methods[i].attributes);
    }
    free(methods);

    for(u2 i = 0; i < attributes_count; i++)
        deleteAttributes(attributes[i]);
    free(attributes);
}

void JavaClass::deleteAttributes(attribute_info attr){
    int type = verifyAttrType(attr.attribute_name_index);
    
    switch(type){
        // Code
        case 2:
            free(attr.info.code.code);
            free(attr.info.code.tables);
            for(u2 i = 0; i < attr.info.code.attributes_count; i++)
                deleteAttributes(attr.info.code.attributes[i]);
            free(attr.info.code.attributes);
            break;
        
        // Inner Classes
        case 5:
            free(attr.info.innerClasses.classes);
            break;

        // Line Number Table
        case 11:
            free(attr.info.lineNumberTable.tables);
            break;
    }
}

void JavaClass::insertByte(u1 byte){
    bytecode *p1, *p2;

    p1 = (bytecode*)malloc(sizeof(bytecode));
    p1->byte = byte;
    p1->next = nullptr;

    if(this->bytes == nullptr){
        this->bytes = p1;
    }
    else {
        p2 = bytes;
        while(p2->next != nullptr)
            p2 = p2->next;
        p2->next = p1;
    }
}

u1 JavaClass::getByte(int nByte){
    u1 byte;
    bytecode *p1;
    int aux = 0;

    if(nByte == 0)
        byte = bytes->byte;
    else{
        p1 = this->bytes;
        while(aux != nByte){
            p1 = p1->next;
            aux++;
        }
        byte = p1->byte;
    }

    return byte;
}

void JavaClass::setClassMagic(){
    int i;
    u4  nMagic;

    for(i = 0; i < 4; i++){
        nMagic = (u4)getByte(i);
        switch(i){
            case 0:
                nMagic = nMagic << 24;
                break;
            case 1:
                nMagic = nMagic << 16;
                break;
            case 2:
                nMagic = nMagic << 8;
                break;
        }
        this->magic += nMagic;
    }
}

void JavaClass::setVersions(int byte){
    u2 nVersion;

    for(int i = byte; i < byte+2; i++){
        nVersion = (u2)getByte(i);
        if (i == byte)
            nVersion = nVersion << 8;
        if (byte == 4)
            this->minor_version += nVersion;
        else
            this->major_version += nVersion;
    }
}

void JavaClass::setCPCount(){
    int i;
    u2 nCPCount;

    for(i = 8; i < 10; i++){
        nCPCount = (u2)getByte(i);
        if (i == 8)
            nCPCount = nCPCount << 8;
        this->constant_pool_count += nCPCount;
    }
}

bool JavaClass::verifyTag(u1 tag){
    bool valid;

    switch(tag){
        case CONSTANT_Utf8:
        case CONSTANT_Integer:
        case CONSTANT_Float:
        case CONSTANT_Long:
        case CONSTANT_Double:
        case CONSTANT_Class:
        case CONSTANT_String:
        case CONSTANT_Fieldref:
        case CONSTANT_Methodref:
        case CONSTANT_InterfaceMethodref:
        case CONSTANT_NameAndType:
        case CONSTANT_MethodHandle:
        case CONSTANT_MethodType:
        case CONSTANT_InvokeDynamic:
            valid = true;
            break;
        default:
            valid = false;
    }

    return valid;
}

void JavaClass::setConstantPool(){
    int bytecode_index = 10;
    u1 tag;
    u2 size = this->constant_pool_count - 1;
    u2 length;

    this->constant_pool = (cp_info*)malloc(sizeof(cp_info)*size);
    for(u2 i = 0; i < size; i++){
        tag = (u1)getByte(bytecode_index);
        bytecode_index++;
        if(verifyTag(tag)){
            this->constant_pool[i].tag = tag;
            switch(tag){
                case CONSTANT_Utf8:
                    // Determina o tamanho da String
                    length = (u2)getByte(bytecode_index) << 8;
                    length += (u2)getByte(bytecode_index+1);
                    bytecode_index += 2;

                    this->constant_pool[i].info.utf8Info.length = length;
                    this->constant_pool[i].info.utf8Info.bytes = (u1*)malloc(sizeof(u1)*(length+1));

                    for(u2 j = 0; j < length; j++)
                        this->constant_pool[i].info.utf8Info.bytes[j] = getByte(bytecode_index+j);
                    bytecode_index += length;   // Avança o tamanho da String                    

                    length = 0;                 // Zera length para próxima String
                    break;
                case CONSTANT_Class:
                case CONSTANT_String:
                case CONSTANT_MethodType:
                    if(tag == CONSTANT_Class) {
                        this->constant_pool[i].info.classInfo.name_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        bytecode_index++;
                    }
                    else if(tag == CONSTANT_String) {
                        this->constant_pool[i].info.stringInfo.string_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        bytecode_index++;
                    }
                    else {
                        this->constant_pool[i].info.methodTypeInfo.descriptor_index =
                                ((u2) getByte(bytecode_index) << 8) + ((u2) getByte(bytecode_index + 1));
                        bytecode_index++;
                    }
                    break;
                case CONSTANT_MethodHandle:
                    this->constant_pool[i].info.methodHandleInfo.reference_kind = getByte(bytecode_index);
                    this->constant_pool[i].info.methodHandleInfo.reference_index =
                            ((u2)getByte(bytecode_index + 1) << 8) + ((u2)getByte(bytecode_index + 2));
                    bytecode_index += 2;
                    break;
                case CONSTANT_Integer:
                case CONSTANT_Float:
                case CONSTANT_Fieldref:
                case CONSTANT_Methodref:
                case CONSTANT_InterfaceMethodref:
                case CONSTANT_NameAndType:
                case CONSTANT_InvokeDynamic:
                    if(tag == CONSTANT_Integer) {
                        this->constant_pool[i].info.integerInfo.bytes = ((u4) getByte(bytecode_index) << 24)
                                                                        + ((u4) getByte(bytecode_index + 1) << 16) +
                                                                        ((u4) getByte(bytecode_index + 2) << 8)
                                                                        + ((u4) getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    else if(tag == CONSTANT_Float) {
                        this->constant_pool[i].info.floatInfo.bytes = ((u4) getByte(bytecode_index) << 24)
                                                                      + ((u4) getByte(bytecode_index + 1) << 16) +
                                                                      ((u4) getByte(bytecode_index + 2) << 8)
                                                                      + ((u4) getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    else if(tag == CONSTANT_Fieldref){
                        this->constant_pool[i].info.fieldrefInfo.class_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        this->constant_pool[i].info.fieldrefInfo.name_and_type_index =
                                ((u2)getByte(bytecode_index + 2) << 8) + ((u2)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    else if(tag == CONSTANT_Methodref){
                        this->constant_pool[i].info.methodrefInfo.class_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        this->constant_pool[i].info.methodrefInfo.name_and_type_index =
                                ((u2)getByte(bytecode_index + 2) << 8) + ((u2)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    else if(tag == CONSTANT_InterfaceMethodref){
                        this->constant_pool[i].info.interfaceMethodrefInfo.class_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        this->constant_pool[i].info.interfaceMethodrefInfo.name_and_type_index =
                                ((u2)getByte(bytecode_index + 2) << 8) + ((u2)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    else if(tag == CONSTANT_NameAndType){
                        this->constant_pool[i].info.nameAndTypeInfo.name_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        this->constant_pool[i].info.nameAndTypeInfo.descriptor_index =
                                ((u2)getByte(bytecode_index + 2) << 8) + ((u2)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    else {
                        this->constant_pool[i].info.invokeDynamicInfo.bootstrap_method_attr_index =
                                ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                        this->constant_pool[i].info.invokeDynamicInfo.name_and_type_index =
                                ((u2)getByte(bytecode_index + 2) << 8) + ((u2)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                    }
                    break;
                case CONSTANT_Long:
                case CONSTANT_Double:
                    if(tag == CONSTANT_Long){
                        this->constant_pool[i].info.longInfo.high_bytes =
                                ((u4)getByte(bytecode_index) << 24) + ((u4)getByte(bytecode_index + 1) << 16) +
                                ((u4)getByte(bytecode_index + 2) << 8) + ((u4)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                        this->constant_pool[++i].tag = tag;
                        this->constant_pool[i].info.longInfo.low_bytes =
                                ((u4)getByte(bytecode_index + 1) << 24) + ((u4)getByte(bytecode_index + 2) << 16) +
                                ((u4)getByte(bytecode_index + 3) << 8) + ((u4)getByte(bytecode_index + 4));
                        bytecode_index += 4;
                    }
                    else {
                        this->constant_pool[i].info.doubleInfo.high_bytes =
                                ((u4)getByte(bytecode_index) << 24) + ((u4)getByte(bytecode_index + 1) << 16) +
                                ((u4)getByte(bytecode_index + 2) << 8) + ((u4)getByte(bytecode_index + 3));
                        bytecode_index += 3;
                        this->constant_pool[++i].tag = tag;
                        this->constant_pool[i].info.doubleInfo.low_bytes =
                                ((u4)getByte(bytecode_index + 1) << 24) + ((u4)getByte(bytecode_index + 2) << 16) +
                                ((u4)getByte(bytecode_index + 3) << 8) + ((u4)getByte(bytecode_index + 4));
                        bytecode_index += 4;
                    }
                    break;
                default:
                    std::cout << (int)tag << " Tag invalida!" << std::endl;
            }
            if(tag != CONSTANT_Utf8)
                bytecode_index++;
        }
    }
}

int JavaClass::getCPSize(){
    int size = 0;
    int length;

    for(u2 i = 0; i < this->constant_pool_count - 1; i++){
        if(this->constant_pool[i].tag != 0){
            size += 1;  // Tag
            switch(this->constant_pool[i].tag){
                case CONSTANT_Utf8:
                    length = (int)constant_pool[i].info.utf8Info.length;
                    size += 2 + length;
                    break;
                case CONSTANT_Class:
                case CONSTANT_String:
                case CONSTANT_MethodType:
                    size += 2;
                    break;
                case CONSTANT_MethodHandle:
                    size += 3;
                    break;
                case CONSTANT_Integer:
                case CONSTANT_Float:
                case CONSTANT_Fieldref:
                case CONSTANT_Methodref:
                case CONSTANT_InterfaceMethodref:
                case CONSTANT_NameAndType:
                case CONSTANT_InvokeDynamic:
                    size += 4;
                    break;
                case CONSTANT_Long:
                case CONSTANT_Double:
                    size += 8;
                    i++;
                    break;
                default:
                    std::cout << /*(int)this->constant_pool[i].tag <<*/ " Tag invalida!" << std::endl;
            }
        }
    }

    // std::cout << size << std::endl;
    return size;
}

void JavaClass::setClassInfo(){
    u2 item;
    this->bytecode_index = getCPSize() + 10;    // Index após o fim da CP
    
    for(int i = 0; i < 7; i++){
        item = (u2)((getByte(this->bytecode_index) << 8) + 
            getByte(this->bytecode_index+1));
        switch(i){
            case 0:
                this->access_flags = item;
                break;
            case 1:
                this->this_class = item;
                break;
            case 2:
                if(getUtf8(constant_pool[this_class-1].info.classInfo.name_index).compare("java/lang/Object") == 0)
                    this->super_class = 0;
                else
                    this->super_class = item;
                break;
            case 3:
                this->interfaces_count = item;
                break;
            case 4:
                this->fields_count = item;
                break;
            case 5:
                this->methods_count = item;
                break;
            case 6:
                this->attributes_count = item;
        }
        this->bytecode_index += 2;
        if(i == 3){
            if((int)this->interfaces_count != 0)
                setInterfaces();
        }
        else if(i == 4){
            if((int)this->fields_count != 0)
                setFields();
        } else if (i == 5){
            if((int)this->methods_count != 0)
                setMethods();
        } else if (i == 6){
            this->attributes = (attribute_info*)malloc(sizeof(attribute_info)
                *this->attributes_count);
            for(int j = 0; j < this->attributes_count; j++)
                setAttribute(&(this->attributes[j]));
        }
    }
}

void JavaClass::setInterfaces(){
    // Aloca o array de Interfaces do .class
    this->interfaces = (u2*)malloc(sizeof(u2)*interfaces_count);

    for(u2 i = 0; i < this->interfaces_count; i++){
        this->interfaces[i] = (u2)((getByte(this->bytecode_index) << 8)
            +(getByte(this->bytecode_index+1)));
        this->bytecode_index += 2;
    }
}

void JavaClass::setFields(){
    // Aloca o array de fields do .class
    this->fields = (field_info*)malloc(sizeof(field_info)*this->fields_count);

    // Field Info
    /* Seta as informações básicas dos métodos do .class
     * 2 byte para cada campo:
     * - access_flags;
     * - name_index;
     * - type_index;
     * - attributes_count;
     */
    for(u2 i = 0; i < this->fields_count; i++){
        for(int j = 0; j < 4; j++){
            switch(j){
                case 0:
                    this->fields[i].access_flags = (u2)(getByte(bytecode_index) << 8);
                    this->fields[i].access_flags += (u2)(getByte(bytecode_index+1));
                    break;
                case 1:
                    this->fields[i].name_index = (u2)(getByte(bytecode_index) << 8);
                    this->fields[i].name_index += (u2)(getByte(bytecode_index+1));
                    break;
                case 2:
                    this->fields[i].type_index = (u2)(getByte(bytecode_index) << 8);
                    this->fields[i].type_index += (u2)(getByte(bytecode_index+1));
                    break;
                case 3:
                    this->fields[i].attributes_count = (u2)(getByte(bytecode_index) << 8);
                    this->fields[i].attributes_count += (u2)(getByte(bytecode_index+1));
                    break;
            }
            bytecode_index += 2;
        }
        this->fields[i].attributes = (attribute_info*)malloc(sizeof(attribute_info)
            *this->fields[i].attributes_count);
        for(int j = 0; j < this->fields[i].attributes_count; j++)
            setAttribute(&(this->fields[i].attributes[j]));
    }
}

void JavaClass::setMethods(){
    // Aloca o array de métodos do .class
    this->methods = (method_info*)malloc(sizeof(method_info)*this->methods_count);

    // Method Info
    /* Seta as informações básicas dos métodos do .class
     * 2 byte para cada campo:
     * - access_flags;
     * - name_index;
     * - type_index;
     * - attributes_count;
     */
    for(u2 i = 0; i < this->methods_count; i++){
        for(int j = 0; j < 4; j++){
            switch(j){
                case 0:
                    this->methods[i].access_flags = (u2)(getByte(bytecode_index) << 8);
                    this->methods[i].access_flags += (u2)(getByte(bytecode_index+1));
                    break;
                case 1:
                    this->methods[i].name_index = (u2)(getByte(bytecode_index) << 8);
                    this->methods[i].name_index += (u2)(getByte(bytecode_index+1));
                    break;
                case 2:
                    this->methods[i].type_index = (u2)(getByte(bytecode_index) << 8);
                    this->methods[i].type_index += (u2)(getByte(bytecode_index+1));
                    break;
                case 3:
                    this->methods[i].attributes_count = (u2)(getByte(bytecode_index) << 8);
                    this->methods[i].attributes_count += (u2)(getByte(bytecode_index+1));
                    break;
            }
            bytecode_index += 2;
        }
        this->methods[i].attributes = (attribute_info*)malloc(sizeof(attribute_info)
            *this->methods[i].attributes_count);
        for(int j = 0; j < this->methods[i].attributes_count; j++)
            setAttribute(&(this->methods[i].attributes[j]));
    }
}

void JavaClass::setAttribute(attribute_info *attr){
    int attrType;
    // Seta a referência para CP
    (*attr).attribute_name_index = (u2)(((getByte(this->bytecode_index)) << 8)+
        (getByte(this->bytecode_index+1)));
    bytecode_index += 2;

    attrType = verifyAttrType((*attr).attribute_name_index);
    if(attrType == 7 || attrType == 13)
        (*attr).attribute_length = 0;
    else{
        // Seta o tamanho do atributo
        (*attr).attribute_length = (u4)((getByte(this->bytecode_index) << 8)
            +(getByte(this->bytecode_index+1) << 16)
            +(getByte(this->bytecode_index+2) << 8)
            +(getByte(this->bytecode_index+3)));
        bytecode_index += 4;
    }

    switch(verifyAttrType((*attr).attribute_name_index)){
        case 1:
            // Constant Value
            (*attr).info.constantValue.constantvalue_index = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;
            break;
        case 2:
            // Code
            (*attr).info.code.max_stack = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;
            
            (*attr).info.code.max_locals = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;
            
            (*attr).info.code.code_length = ((u4)getByte(bytecode_index) << 24)
                +((u4)getByte(bytecode_index+1) << 16)+((u4)getByte(bytecode_index+2) << 8)
                +((u4)getByte(bytecode_index+3));
            bytecode_index += 4;
            
            (*attr).info.code.code = (u1*)malloc(sizeof(u1)*(*attr).info.code.code_length);
            for(int i = 0; i < (int)(*attr).info.code.code_length; i++, bytecode_index++)
                (*attr).info.code.code[i] = getByte(bytecode_index);
            
            (*attr).info.code.exception_table_length = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            (*attr).info.code.tables = (exception_table*)malloc(
                sizeof(exception_table)*(*attr).info.code.exception_table_length);
            bytecode_index += 2;

            for(int i = 0; i < (*attr).info.code.exception_table_length; i++){
                (*attr).info.code.tables[i].start_pc = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.code.tables[i].end_pc = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.code.tables[i].handler_pc = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.code.tables[i].catch_type = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;
            }
            
            (*attr).info.code.attributes_count = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;

            (*attr).info.code.attributes = (attribute_info*)malloc(
                sizeof(attribute_info)*(*attr).info.code.attributes_count);
            for(int i = 0; i < (*attr).info.code.attributes_count; i++)
                setAttribute(&(*attr).info.code.attributes[i]);
            break;
        case 4:
            // Exeception
            (*attr).info.exceptions.number_of_exceptions =
                    ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
            bytecode_index += 2;

            (*attr).info.exceptions.exception_index_table = (u2*)malloc(sizeof(u2)*
                (*attr).info.exceptions.number_of_exceptions);
            
            for(int i = 0; i < (*attr).info.exceptions.number_of_exceptions; i++) {
                (*attr).info.exceptions.exception_index_table[i] =
                        ((u2) getByte(bytecode_index) << 8) + ((u2) getByte(bytecode_index + 1));
                bytecode_index += 2;
            }
            break;
        case 5:
            // InnerClasses
            (*attr).info.innerClasses.number_of_classes = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;

            (*attr).info.innerClasses.classes = (Classes*)malloc(sizeof(Classes)*
                (*attr).info.innerClasses.number_of_classes);
            for(int i = 0; i < (*attr).info.innerClasses.number_of_classes; i++){
                (*attr).info.innerClasses.classes[i].inner_class_info_index = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.innerClasses.classes[i].outer_class_info_index = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.innerClasses.classes[i].inner_name_index = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.innerClasses.classes[i].inner_class_access_flags = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;
            }
            break;
        case 6:
            // EnclosingMethod
            (*attr).info.enclosingMethod.class_index = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;

            (*attr).info.enclosingMethod.method_index = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;
            break;
        case 7:
            // Synthetic
            // O atributo "synthetic" só possui name_index e length = 0!
            // DO NOTHING
            break;
        case 8:
            // Signature
            (*attr).info.signature.signature_index = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;
            break;
        case 9:
            // SourceFile
            (*attr).info.sourceFile.sourcefile_index = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;
            break;
        case 10:
            // SourceDebugExtension
            (*attr).info.sourceDebugExtension.debug_extension = (u1*)malloc(sizeof(u1)
                *(*attr).attribute_length);
            for(u2 i = 0; i < (*attr).attribute_length; i++, bytecode_index++)
                (*attr).info.sourceDebugExtension.debug_extension[i] = getByte(bytecode_index);
            break;
        case 11:
            // LineNumberTable
            (*attr).info.lineNumberTable.line_number_table_length = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;

            (*attr).info.lineNumberTable.tables = (line_number_table*)malloc(sizeof(
                line_number_table)*(*attr).info.lineNumberTable.line_number_table_length);
            for(int i = 0; i < (*attr).info.lineNumberTable.line_number_table_length; i++){
                (*attr).info.lineNumberTable.tables[i].start_pc = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;

                (*attr).info.lineNumberTable.tables[i].line_number = ((u2)getByte(bytecode_index) << 8)
                    +((u2)getByte(bytecode_index+1));
                bytecode_index += 2;
            }
            break;
        case 12:
            // LocalVariableTable
            (*attr).info.localVariableTable.local_variable_table_length = ((u2)getByte(bytecode_index) << 8)
                +((u2)getByte(bytecode_index+1));
            bytecode_index += 2;

            (*attr).info.localVariableTable.tables = (local_variable_table*)malloc(
                sizeof(local_variable_table)*(*attr).info.localVariableTable.local_variable_table_length);
            for(int i = 0; i < (*attr).info.localVariableTable.local_variable_table_length; i++){
                (*attr).info.localVariableTable.tables[i].start_pc =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariableTable.tables[i].length =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariableTable.tables[i].name_index =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariableTable.tables[i].descriptor_index =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariableTable.tables[i].index =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;
            }
            break;
        case 13:
            (*attr).info.localVariabelTypeTable.local_variable_type_table_length =
                    ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
            bytecode_index += 2;
            
            (*attr).info.localVariabelTypeTable.tables = (local_variable_type_table*)malloc(
                sizeof(local_variable_type_table)*(*attr).info.localVariabelTypeTable.local_variable_type_table_length);

            for(int i = 0; i < (*attr).info.localVariabelTypeTable.local_variable_type_table_length; i++){
                (*attr).info.localVariabelTypeTable.tables[i].start_pc =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariabelTypeTable.tables[i].length =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariabelTypeTable.tables[i].name_index =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariabelTypeTable.tables[i].signature_index =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.localVariabelTypeTable.tables[i].index =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;
            }
            break;
        case 14:
            // Deprecated
            // O atributo "deprecated" só possui name_index e length = 0!
            // DO NOTHING
            break;
        case 19:
            // BootstrapMethods
            (*attr).info.bootstrapMethods.num_bootstrap_methods =
                    ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
            bytecode_index += 2;
            
            (*attr).info.bootstrapMethods.methods = (bootstrap_methods*)malloc(
                sizeof(bootstrap_methods)*(*attr).info.bootstrapMethods.num_bootstrap_methods);
            
            for(int i = 0; i < (*attr).info.bootstrapMethods.num_bootstrap_methods; i++){
                (*attr).info.bootstrapMethods.methods[i].bootstrap_method_ref =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.bootstrapMethods.methods[i].num_bootstrap_arguments =
                        ((u2)getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                bytecode_index += 2;

                (*attr).info.bootstrapMethods.methods[i].bootstrap_arguments = (u2*)malloc(
                    sizeof(u2)*(*attr).info.bootstrapMethods.methods[i].num_bootstrap_arguments);

                for(int j = 0; j < (*attr).info.bootstrapMethods.methods[i].num_bootstrap_arguments; j++) {
                    (*attr).info.bootstrapMethods.methods[i].bootstrap_arguments[j] =
                            ((u2) getByte(bytecode_index) << 8) + ((u2)getByte(bytecode_index + 1));
                    bytecode_index += 2;
                }
            }
            break;
        default:
            /*
             * Qualquer caso não tratado pelo Switch é um atributo inválido
             * (não implementado). A JVM irá apenas ignorar em silêncio os seguintes
             * atributos:
             * - StackMapTable;
             * - RuntimeVisibleAnnotations;
             * - RuntimeInvisibleAnnotations;
             * - RuntimeVisibleParameterAnnotations;
             * - RuntimeInvisibleParameterAnnotations;
             * - AnnotationDefault.
             * 
             * A instrução abaixo apenas avança para o próximo atributo a ser lido.
             */
            bytecode_index += (int)(*attr).attribute_length;
    }
}
 
int JavaClass::verifyAttrType(u2 name_index){
    int type = 0;
    std::string typeName = getUtf8(name_index);
 
    // Verifica qual tipo de atributo, associa 'type' ao tipo certo
    if(typeName.compare("ConstantValue") == 0)
        type = ATT_CONST_VALUE;
    else if(typeName.compare("Code") == 0)
        type = ATT_CODE;
    else if(typeName.compare("StackMapTable") == 0)
        type = ATT_STACK_MAP_TABLE;
    else if(typeName.compare("Exceptions") == 0)
        type = ATT_EXCEPTIONS;
    else if(typeName.compare("InnerClasses") == 0)
        type = ATT_INNER_CLASSES;
    else if(typeName.compare("EnclosingMethod") == 0)
        type = ATT_ENCLO_METHOD;
    else if(typeName.compare("Synthetic") == 0)
        type = ATT_SYNTHETIC;
    else if(typeName.compare("Signature") == 0)
        type = ATT_SIGNATURE;
    else if(typeName.compare("SourceFile") == 0)
        type = ATT_SRC_FILE;
    else if(typeName.compare("SourceDebugExtension") == 0)
        type = ATT_SRC_DBG_EXT;
    else if(typeName.compare("LineNumberTable") == 0)
        type = ATT_LINE_NUM_TABLE;
    else if(typeName.compare("LocalVariableTable") == 0)
        type = ATT_LOCAL_VAR_TABLE;
    else if(typeName.compare("LocalVariableTypeTable") == 0)
        type = ATT_LCL_VAR_T_TABLE;
    else if(typeName.compare("Deprecated") == 0)
        type = ATT_DEPRECATED;
    else if(typeName.compare("RuntimeVisibleAnnotations") == 0)
        type = ATT_RT_V_ANNOT;
    else if(typeName.compare("RuntimeInvisibleAnnotations") == 0)
        type = ATT_RT_IN_ANNOT;
    else if(typeName.compare("RuntimeVisibleParameterAnnotations") == 0)
        type = ATT_RT_V_P_ANNOT;
    else if(typeName.compare("RuntimeInvisibleParameterAnnotations") == 0)
        type = ATT_RT_IN_P_ANNOT;
    else if(typeName.compare("AnnotationDefault") == 0)
        type = ATT_ANNOT_DEFAULT;
    else if(typeName.compare("BootstrapMethods") == 0)
        type = ATT_BOOT_METHOD;
 
    // Retorna o tipo de atributo
    return type;
}

std::string JavaClass::getUtf8 (u2 name_index){
    cp_info cp_entry;
    u2 length;
    char* name;
    std::string typeName;
 
    // Busca a referência na CP
    cp_entry = constant_pool[name_index-1];
   
    // Verifica o tamanho da string UTF-8
    length = cp_entry.info.utf8Info.length;
   
    // Aloca de acordo com o tamanho 'length' retornado
    name = (char*)malloc(sizeof(char)*length);
 
    // Recupera os bytes UTF-8
    for(u2 i = 0; i < length; i++)
        name[i] = cp_entry.info.utf8Info.bytes[i];
 
    // Passa os bytes de char* para string
    for(u2 i = 0; i < length; i++)
        typeName += name[i];
   
    // Desaloca os bytes char*
    free(name);
 
    return typeName;
}

bool JavaClass::isMethodAccessFlagSet(u2 method_index, MethodAccessFlag search_flag){
    // TODO: fill with other flags
    // see: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.5-200-A.1
    u2 access_value = methods[method_index].access_flags;
    switch(search_flag){
        case ACC_PUBLIC:
            return (access_value & 0x0001);
        default: break;
    }

    return false;
}