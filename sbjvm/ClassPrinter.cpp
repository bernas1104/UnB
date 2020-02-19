#include "include/ClassPrinter.hpp"

ClassPrinter::ClassPrinter(){
    // TODO
}

ClassPrinter::~ClassPrinter(){
    // TODO
}

void ClassPrinter::setClass(JavaClass jc){
    this->jc = jc;
}

void ClassPrinter::printClassFile(){
    u2 flag;

    printVersion(jc.minor_version, jc.major_version);
    std::cout << "Constant Pool Count = " << (u2)jc.constant_pool_count - 1 << std::endl;
    std::cout << "\n";
    
    flag = jc.access_flags;
    std::cout << "Access Flags = ";
    if(flag & 0x0001)
        std::cout << "public ";
    if((flag >> 4) & 0x0001)
        std::cout << "final ";
    if((flag >> 5) & 0x0001)
        std::cout << "super ";
    if((flag >> 9) & 0x0001)
        std::cout << "interface ";
    if((flag >> 10) & 0x0001)
        std::cout << "abstract ";
    if((flag >> 12) & 0x0001)
        std::cout << "synthetic ";
    if((flag >> 13) & 0x0001)
        std::cout << "annotation ";
    if((flag >> 14) & 0x0001)
        std::cout << "enum";
    std::cout << std::endl;
    std::cout << "This Class = " << constPoolRef((u2)jc.this_class) << std::endl;
    std::cout << "Super Class = ";
    if(!jc.super_class)
        std::cout << jc.super_class << std::endl;
    else
        std::cout << constPoolRef((u2)jc.super_class) << std::endl;
    std::cout << "Interfaces Count = " << (u2)jc.interfaces_count << std::endl;
    std::cout << "Fields Count = " << (u2)jc.fields_count << std::endl;
    std::cout << "Methods Count = " << (u2)jc.methods_count << std::endl;

    if(jc.interfaces_count != 0){
        std::cout << "\nInterfaces\n\n";
        for(u2 i = 0; i < jc.interfaces_count; i++)
            std::cout << i << ": Name Index = " << constPoolRef(jc.interfaces[i]) << std::endl;
    }
    
    if(jc.fields_count != 0){
        std::cout << "\nFields:\n\n";
        for(u2 i = 0; i < jc.fields_count; i++){
                // see: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.5-200-A.1
                flag = jc.fields[i].access_flags;
                std::cout << "Access Flags = ";
                if(flag & 0x0001)
                    std::cout << "public ";
                if((flag >> 1) & 0x0001)
                    std::cout << "private ";
                if((flag >> 2) & 0x0001)
                    std::cout << "protected ";
                if((flag >> 3) & 0x0001)
                    std::cout << "static ";
                if((flag >> 4) & 0x0001)
                    std::cout << "final ";
                if((flag >> 6) & 0x0001)
                    std::cout << "volatile ";
                if((flag >> 7) & 0x0001)
                    std::cout << "transient ";
                if((flag >> 13) & 0x0001)
                    std::cout << "synthetic ";
                if((flag >> 14) & 0x0001)
                    std::cout << "enum";
                std::cout << std::endl;
            std::cout << "- Name Index = " << constPoolRef((u2)jc.fields[i].name_index) << std::endl;
            std::cout << "- Type Index = " << constPoolRef((u2)jc.fields[i].type_index) << std::endl;
            std::cout << "- Attributes Count = " << (u2)jc.fields[i].attributes_count << std::endl;
            if(jc.fields[i].attributes_count != 0){
                for(u2 j = 0; j < jc.fields[i].attributes_count; j++){
                    printAttribute(jc.fields[i].attributes[j]);
                    std::cout << "\n";
                }
            }
            std::cout << "\n";
        }
    }

    if(jc.methods_count != 0){
        std::cout << "\nMethods:\n\n";
        for(u2 i = 0; i < jc.methods_count; i++){
                flag = jc.methods[i].access_flags;
                std::cout << "Access Flags = ";
                if(flag & 0x0001)
                    std::cout << "public ";
                if((flag >> 1) & 0x0001)
                    std::cout << "private ";
                if((flag >> 2) & 0x0001)
                    std::cout << "protected ";
                if((flag >> 3) & 0x0001)
                    std::cout << "static ";
                if((flag >> 4) & 0x0001)
                    std::cout << "final ";
                if((flag >> 5) & 0x0001)
                    std::cout << "synchornized ";
                if((flag >> 6) & 0x0001)
                    std::cout << "bridge ";
                if((flag >> 7) & 0x0001)
                    std::cout << "varargs ";
                if((flag >> 8) & 0x0001)
                    std::cout << "native ";
                if((flag >> 9) & 0x0001)
                    std::cout << "abstract ";
                if((flag >> 10) & 0x0001)
                    std::cout << "strict ";
                if((flag >> 11) & 0x0001)
                    std::cout << "synthetic";
                std::cout << std::endl;
            std::cout << "- Name Index = " << constPoolRef((u2)jc.methods[i].name_index) << std::endl;
            std::cout << "- Type Index = " << constPoolRef((u2)jc.methods[i].type_index) << std::endl;
            std::cout << "- Attributes Count = " << (u2)jc.methods[i].attributes_count << std::endl;
            if(jc.methods[i].attributes_count != 0){
                for(u2 j = 0; j < jc.methods[i].attributes_count; j++){
                    printAttribute(jc.methods[i].attributes[j]);
                    std::cout << "\n";
                }
            }
            std::cout << "\n";
        }
    }

    if(jc.attributes_count != 0){
        std::cout << "Attributes:\n";
            for(u2 i = 0; i < jc.attributes_count; i++){
                printAttribute(jc.attributes[i]);
            }
    }
}

void ClassPrinter::printVersion(u2 minor, u2 major){
    for(int i = 0; i < 2; i++){
        if(!i){
            printf("Minor Version: ");
            switch(minor){
                case JAVA1_2:
                    printf("Java 1.2\n");
                    break;
                case JAVA1_3:
                    printf("Java 1.3\n");
                    break;
                case JAVA1_4:
                    printf("Java 1.4\n");
                    break;
                case JAVA5:
                    printf("Java 5\n");
                    break;
                case JAVA6:
                    printf("Java 6\n");
                    break;
                case JAVA7:
                    printf("Java 7\n");
                    break;
                case JAVA8:
                    printf("Java 8\n");
                    break;
                case JAVA9:
                    printf("Java 9\n");
                    break;
                case JAVA10:
                    printf("Java 10\n");
                    break;
                case JAVA11:
                    printf("Java 11\n");
                    break;
                default:
                    printf("Java 0\n");
            }
        } else {
            printf("Major Version: ");
            switch(major){
                case JAVA1_2:
                    printf("Java 1.2\n");
                    break;
                case JAVA1_3:
                    printf("Java 1.3\n");
                    break;
                case JAVA1_4:
                    printf("Java 1.4\n");
                    break;
                case JAVA5:
                    printf("Java 5\n");
                    break;
                case JAVA6:
                    printf("Java 6\n");
                    break;
                case JAVA7:
                    printf("Java 7\n");
                    break;
                case JAVA8:
                    printf("Java 8\n");
                    break;
                case JAVA9:
                    printf("Java 9\n");
                    break;
                case JAVA10:
                    printf("Java 10\n");
                    break;
                case JAVA11:
                    printf("Java 11\n");
                    break;
                default:
                    printf("Java 0\n");
            }
        }
    }
}

void ClassPrinter::printConstPool(){
    u2 length;
    std::cout << "\nEntry\t\t|\tType\t\t|\tValue\n";
    std::cout << "-------------------------------------------------------\n";
    for(u2 i = 0; i < jc.constant_pool_count-1; i++){
            std::cout << i+1 << "\t\t|\t";
            switch(jc.constant_pool[i].tag){
                case CONSTANT_Utf8:
                    std::cout << "UTF-8\t\t|\t";
                    length = jc.constant_pool[i].info.utf8Info.length;
                    for(u2 j = 0; j < length; j++)
                        std::cout << jc.constant_pool[i].info.utf8Info.bytes[j];
                    break;
                case CONSTANT_Integer:
                    std::cout << "Integer\t\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.integerInfo.bytes;
                    break;
                case CONSTANT_Float:
                    std::cout << "Float\t\t|\t";
                        std::cout << (int)jc.constant_pool[i].info.floatInfo.bytes;
                    break;
                case CONSTANT_Long:
                    std::cout << "Long\t\t|\t";
                    std::cout << "H: " << (int)jc.constant_pool[i].info.longInfo.high_bytes << std::endl;
                    std::cout << (++i)+1 << "\t\t|\t";
                    std::cout << "Long\t\t|\t";
                    std::cout << "L: " << (int)jc.constant_pool[i].info.longInfo.low_bytes;
                    break;
                case CONSTANT_Double:
                    std::cout << "Double\t\t|\t";
                    std::cout << "H: " << (int)jc.constant_pool[i].info.doubleInfo.high_bytes << std::endl;
                    std::cout << (++i)+1 << "\t\t|\t";
                    std::cout << "Double\t\t|\t";
                    std::cout << "L: " << (int)jc.constant_pool[i].info.doubleInfo.low_bytes;
                    break;
                case CONSTANT_Class:
                    std::cout << "Class\t\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.classInfo.name_index;
                    break;
                case CONSTANT_String:
                    std::cout << "String\t\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.stringInfo.string_index;
                    break;
                case CONSTANT_Fieldref:
                    std::cout << "Fieldref\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.fieldrefInfo.class_index
                        << " " << (int)jc.constant_pool[i].info.fieldrefInfo.name_and_type_index;
                    break;
                case CONSTANT_Methodref:
                    std::cout << "Methodref\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.methodrefInfo.class_index
                        << " " << (int)jc.constant_pool[i].info.methodrefInfo.name_and_type_index;
                    break;
                case CONSTANT_InterfaceMethodref:
                    std::cout << "InterfaceMethodref\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.interfaceMethodrefInfo.class_index
                        << " " << (int)jc.constant_pool[i].info.interfaceMethodrefInfo.name_and_type_index;
                    break;
                case CONSTANT_NameAndType:
                    std::cout << "NameAndType\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.nameAndTypeInfo.name_index 
                        << " " << (int)jc.constant_pool[i].info.nameAndTypeInfo.descriptor_index;
                    break;
                case CONSTANT_MethodHandle:
                    std::cout << "MethodHandle\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.methodHandleInfo.reference_kind
                        << " " << (int)jc.constant_pool[i].info.methodHandleInfo.reference_index;
                    break;
                case CONSTANT_MethodType:
                    std::cout << "MethodType\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.methodTypeInfo.descriptor_index;
                    break;
                case CONSTANT_InvokeDynamic:
                    std::cout << "InvokeDynamic\t|\t";
                    std::cout << (int)jc.constant_pool[i].info.invokeDynamicInfo.bootstrap_method_attr_index
                        << " " << (int)jc.constant_pool[i].info.invokeDynamicInfo.name_and_type_index;
                    break;
                default:
                    std::cout << "\t\t|";
            }
            std::cout << std::endl;
    }
}

void ClassPrinter::printAttribute(attribute_info attr){
    int typeName = verifyAttrType(attr.attribute_name_index);
    u2 cp_entry;
    u4 pos, aux, dft, high, low, npairs, value, offset;
    int branch, max;

    if(typeName == ATT_CONST_VALUE){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
        std::cout << "\tConstant Value Index" << constPoolRef((int)attr.info.constantValue.constantvalue_index) << std::endl;
    }
    
    if(typeName == ATT_CODE){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
        std::cout << "\tMax stack: " << (int)attr.info.code.max_stack << "\n";
        std::cout << "\tMax locals: " << (int)attr.info.code.max_locals << "\n";

        std::cout << "\tCode Length: " << (int)attr.info.code.code_length << std::endl;
        std::cout << "\tCode: " << std::endl;
        for(u4 k = 0; k < attr.info.code.code_length; k++){
            /* -- Alinhar o print da instrução --*/
            if (k < 10)
                std::cout << "\t  " << k << ":   ";
            else if(k < 100)
                std::cout << "\t  " << k << ":  ";
            else
                std::cout << "\t  " << k << ": ";
            if((attr.info.code.code[k] >= 0x12) && (attr.info.code.code[k] <= 0x14))
                std::cout << mapInstructions[(int)attr.info.code.code[k]].name << "\t";
            else
                std::cout << mapInstructions[(int)attr.info.code.code[k]].name;
            /* -- Alinhar o print da instrução --*/
            
            /* -- Table/Lookupswitch -- */
            if((attr.info.code.code[k] == 0xaa) || (attr.info.code.code[k] == 0xab)){
                /*
                 * Armazena a posição da instrução table/lookupswitch
                 * para realizar o cálculo do offset.
                 */
                pos = k;

                /* -- Calculo do padding -- */
                switch(k%4){
                    case 0:
                        k += 4;
                        break;
                    case 1:
                        k += 3;
                        break;
                    case 2:
                        k += 2;
                        break;
                    case 3:
                        k++;
                        break;
                    default:
                        std::cout << "Error!" << std::endl;
                }
                /* -- Calculo do padding -- */

                /* -- Default -- */
                dft  = ((attr.info.code.code[k] << 24) + (attr.info.code.code[k + 1] << 16)
                        +(attr.info.code.code[k + 2] << 8) + (attr.info.code.code[k + 3]));
                k += 4;
                
                /* -- Tableswitch -- */
                if(attr.info.code.code[pos] == 0xaa){
                    /* -- Low -- */    
                    low  = ((attr.info.code.code[k] << 24) + (attr.info.code.code[k + 1] << 16)
                            +(attr.info.code.code[k + 2] << 8) + (attr.info.code.code[k + 3]));
                    k += 4;
                    
                    /* -- High -- */
                    high = ((attr.info.code.code[k] << 24) + (attr.info.code.code[k + 1] << 16)
                            +(attr.info.code.code[k + 2] << 8) + (attr.info.code.code[k + 3])); // onde esta k + 3 tinha somente um k, por isso k += 3
                    k += 3;
                    
                    std::cout << "{ // " << low << " to " << high << std::endl;
                    for(u4 l = low; l <= high; l++){
                        k++;
                        std::cout << "\t\t\t" << l << ": ";
                    
                        aux = ((attr.info.code.code[k] << 24) + (attr.info.code.code[k + 1] << 16)
                                +(attr.info.code.code[k + 2] << 8) + (attr.info.code.code[k + 3])+pos); // onde esta k + 3 tinha somente um k, por isso k += 3
                        k += 3;
                    
                        std::cout << aux << std::endl;
                    }
                    std::cout << "\t\t  default: " << dft+pos << std::endl;
                    std::cout << "\t}";
                }
                /* -- Tableswitch -- */

                /* -- Lookupswitch -- */
                else{
                    // Calcula a quantidade de pares
                    npairs = ((attr.info.code.code[k] << 24) + (attr.info.code.code[k + 1] << 16)
                                +(attr.info.code.code[k + 2] << 8)+(attr.info.code.code[k + 3]));
                    k += 4;
                    
                    std::cout << "{ // " <<  npairs << std::endl;
                    for(u4 l = 0; l < npairs; l++/*, k += 8*/){
                        value  = ((attr.info.code.code[k] << 24) + (attr.info.code.code[k + 1] << 16)
                                    +(attr.info.code.code[k + 2] << 8) + (attr.info.code.code[k + 3]));
                        k += 4;
                        
                        offset = ((attr.info.code.code[k] << 24)+(attr.info.code.code[k + 1] << 16)
                                    +(attr.info.code.code[k + 2] << 8)+(attr.info.code.code[k + 3]));
                        k += 4;
                        
                        std::cout << "\t\t";
                        std::cout << value << ": " << pos+offset << std::endl;
                    }
                    std::cout << "\t\tdefault: " << dft+pos << std::endl;
                    std::cout << "\t\t}";
                    k--;
                }
                /* -- Lookupswitch -- */
            }
            /* -- Table/Lookupswitch -- */

            /* -- Instruções COM consulta à CP -- */
            else if(((attr.info.code.code[k] >= 0x12) && (attr.info.code.code[k] <= 0x14))
                ||((attr.info.code.code[k] >= 0xb2) && (attr.info.code.code[k] <= 0xbb))
                ||(attr.info.code.code[k] == 0xbd)
                ||(attr.info.code.code[k] == 0xb9)
                ||((attr.info.code.code[k] == 0xc0) && (attr.info.code.code[k] == 0xc1))
                ||(attr.info.code.code[k] == 0xc5)){
                
                /* -- ldc -> usa apenas 1byte de index -- */
                if(attr.info.code.code[k] == 0x12){
                    k++;
                    std::cout << "\t#" << (int)attr.info.code.code[k];
                    std::cout << " //  ";
                    cp_entry = (attr.info.code.code[k]);
                    std::cout << constPoolRef(cp_entry);
                }

                /* -- invokedynamic e invokeinterface; 4 bytes -- */
                else if(attr.info.code.code[k] == 0xba || attr.info.code.code[k] == 0xb9){
                    std::cout << "\t#" << (int)((attr.info.code.code[k+1] << 8)+(attr.info.code.code[k+2]));

                    // invokedynamic
                    if(attr.info.code.code[k] == 0xba){
                        k++;
                        std::cout << " //  ";
                        
                        cp_entry = ((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1]));
                        k += 2;
                        std::cout << constPoolRef(cp_entry);

                        if(attr.info.code.code[k++] != 0x00)
                            std::cout << "ERROR!";
                        if(attr.info.code.code[k] != 0x00)
                            std::cout << "ERROR!";
                    }
                    
                    // invokeinterface
                    else{
                        k++;
                        std::cout << "\t//  ";
                        cp_entry = ((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1]));
                        k += 2;
                        std::cout << constPoolRef(cp_entry);

                        std::cout << " " << attr.info.code.code[k++];
                        
                        if(attr.info.code.code[k] != 0x00)
                            std::cout << "ERROR!";
                    }
                }

                /* -- Todo o resto usa 2 bytes -- */
                else{
                    std::cout << "\t#" << (int)((attr.info.code.code[k+1] << 8)+(attr.info.code.code[k+2]));
                    if(attr.info.code.code[k] == 0xc5)
                        std::cout << ", " << (int)attr.info.code.code[k+3];
                    k++;
                    std::cout << " //  ";
                    cp_entry = ((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1]));
                    k++;
                    std::cout << constPoolRef(cp_entry);
                    if(attr.info.code.code[k-2] == 0xc5)
                        k++;
                }
            }
            /* -- Instruções COM consulta à CP -- */

            /* -- Instruções SEM consulta à CP -- */
            else{
                /* -- Instruções de Branch 1 -- */
                if((attr.info.code.code[k] >= 0x99)&&(attr.info.code.code[k] <= 0xa8)){
                    if((attr.info.code.code[k] >= 0x9f)&&((attr.info.code.code[k] <= 0xa4))){
                        k++;
                        branch = (int16_t)(k+((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1])-1));
                        k++;
                        std::cout << "\t" << branch;
                    }
                    else{
                        k++;
                        branch = (int16_t)(k+((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1])-1));
                        k++;
                        std::cout << "\t" << branch;
                    }
                }
                /* -- Instruções de Branch 1 -- */

                /* -- Instruções de Branch 2 -- */
                else if((attr.info.code.code[k] >= 0xc6)&&(attr.info.code.code[k] <= 0xc9)){
                    /* -- Instruções de Branch Wide (4bytes) -- */
                    if((attr.info.code.code[k] == 0xc8) || attr.info.code.code[k] == 0xc9){
                        k++;
                        branch = (int32_t)(k+((attr.info.code.code[k] << 24)+(attr.info.code.code[k + 1] << 16)
                            +(attr.info.code.code[k + 2] << 8)+(attr.info.code.code[k + 3])-1))-1;
                        k += 3;
                        std::cout << "\t" << branch;
                    }
                    /* -- Instruções de Branch Wide (4bytes) -- */

                    /* -- Instruções de Branch -- */
                    else{
                        k++;
                        branch = (int16_t)(k+((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1])-1))-1;
                        k++;
                        std::cout << "\t" << branch;
                    }
                    /* -- Instruções de Branch -- */
                }
                /* -- Instruções de Branch 2 -- */

                /* 
                 * Restante das Instruções:
                 * Contém as instruções sem argumentos (operand stack), e
                 * as instruções que fazem referência ao vetor de variáveis locais.
                 */
                else{
                    if(mapInstructions.at(attr.info.code.code[k]).args != 0){
                        if(attr.info.code.code[k] == 0x11){
                            k++;
                            std::cout << "\t" << (int)((attr.info.code.code[k] << 8)+(attr.info.code.code[k + 1]));
                            k++;
                        }
                        else{
                            // Armazena o byte da instrução
                            aux = k;

                            // Avança para o 1o argumento
                            k++;
                            std::cout << "\t";
                            
                            /*
                            * Armazena o limite dos argumentos para auxiliar
                            * na impressão seguindo o padrão:
                            * x, y, z...
                            */
                            max = mapInstructions[attr.info.code.code[aux]].args - 1;
                            
                            // Printa os argumentos
                            for(int l = 0; l < mapInstructions[attr.info.code.code[aux]].args; l++, k++){
                                if(l < max)
                                    std::cout << (int)attr.info.code.code[k] << ", ";
                                else
                                    std::cout << (int)attr.info.code.code[k];
                            }
                            k--;
                        }
                    }
                }
                /* Restante das Instuções */
            }
            /* -- Instruções SEM consulta à CP -- */
            std::cout << "\n";
        }

        if(attr.info.code.exception_table_length){
            std::cout << "Exception Table Length: " << attr.info.code.exception_table_length << std::endl;
            for(u2 k = 0; k < attr.info.code.exception_table_length; k++){
                std::cout << "\tStart PC: " << (int)attr.info.code.tables[k].start_pc << std::endl;
                std::cout << "\tEnd PC:" << (int)attr.info.code.tables[k].end_pc << std::endl;
                std::cout << "\tHandler PC: " << (int)attr.info.code.tables[k].handler_pc << std::endl;
                std::cout << "\tCatch Type: ";
                if(!attr.info.code.tables[k].catch_type)
                    std::cout << attr.info.code.tables[k].catch_type << std::endl;
                else{
                    std::cout << constPoolRef(attr.info.code.tables[k].catch_type);
                    std::cout << "\n";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }

        if(attr.info.code.attributes_count){
            std::cout << "Code Attributes: " << std::endl;
            for(u2 k = 0; k < attr.info.code.attributes_count; k++){
                printAttribute(attr.info.code.attributes[k]);
            }
        }
    }

    if(typeName == ATT_EXCEPTIONS){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
        std::cout << "\tNumber of Exceptions: " << (int)attr.info.exceptions.number_of_exceptions << std::endl;
        for(u2 k = 0; k < attr.info.exceptions.number_of_exceptions; k++)
            std::cout << "\t\tException Index: " << constPoolRef((int)attr.info.exceptions.exception_index_table[k]) << std::endl;
    }

    if(typeName == ATT_INNER_CLASSES){
        u2 flag;
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
        std::cout << "\t\tNumber of Classes: " << (int)attr.info.innerClasses.number_of_classes << std::endl;
        for(u2 k = 0; k < attr.info.innerClasses.number_of_classes; k++){
            std::cout << "\t\t" << k+1 << "o Entry: " << std::endl;
            std::cout << "\t\t\tInner Class Index: " << constPoolRef(attr.info.innerClasses.classes[k].inner_class_info_index) << std::endl;
            if(attr.info.innerClasses.classes[k].outer_class_info_index != 0)
                std::cout << "\t\t\tOutter Class Index: " << constPoolRef(attr.info.innerClasses.classes[k].outer_class_info_index) << std::endl;
            if(attr.info.innerClasses.classes[k].inner_name_index != 0)
                std::cout << "\t\t\tInner Class Name Index: " << constPoolRef(attr.info.innerClasses.classes[k].inner_name_index) << std::endl;
            std::cout << "\t\t\tInner Class Access Flags: " << std::endl;
            flag = attr.info.innerClasses.classes[k].inner_class_access_flags;
            if(flag & 0x0001)
                std::cout << "public ";
            if((flag >> 1) & 0x0001)
                std::cout << "private ";
            if((flag >> 4) & 0x0001)
                std::cout << "final ";
            if((flag >> 5) & 0x0001)
                std::cout << "super ";
            if((flag >> 9) & 0x0001)
                std::cout << "interface";
            if((flag >> 10) & 0x0001)
                std::cout << "abstract ";
            if((flag >> 12) & 0x0001)
                std::cout << "synthetic ";
            if((flag >> 13) & 0x0001)
                std::cout << "annotation ";
            if((flag >> 14) & 0x0001)
                std::cout << "enum";
            std::cout << "\n";
        }
    }

    if(typeName == ATT_SYNTHETIC){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
    }

    if(typeName == ATT_LINE_NUM_TABLE){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
        std::cout << "\t\tLine Number Table Length: " << (int)attr.info.lineNumberTable.line_number_table_length << std::endl;
        for(u2 k = 0; k < attr.info.lineNumberTable.line_number_table_length; k++){
            std::cout << "\t\t" << k+1 << "o Entry: " << std::endl;
            std::cout << "\t\t\tStart PC: " << (int)attr.info.lineNumberTable.tables[k].start_pc << std::endl;
            std::cout << "\t\t\tLine Number: " << (int)attr.info.lineNumberTable.tables[k].line_number << std::endl;
            std::cout << "\n";
        }
    }

    if(typeName == ATT_SRC_FILE){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
        std::cout << "\t\tSource File Index: " << constPoolRef((int)attr.info.sourceFile.sourcefile_index) << std::endl;
    }

    if(typeName == ATT_LOCAL_VAR_TABLE){
        std::cout << "\tCP Index: " << constPoolRef(attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << attr.attribute_length << std::endl;
        std::cout << "\t\tLocal Variable Table Length: " << attr.info.localVariableTable.local_variable_table_length << std::endl;
        for(u2 k = 0; k < attr.info.localVariableTable.local_variable_table_length; k++){
            std::cout << "\t\t" << k+1 << "o Entry: " << std::endl;
            std::cout << "\t\t\tStart PC: " << attr.info.localVariableTable.tables[k].start_pc << std::endl;
            std::cout << "\t\t\tLength: " << attr.info.localVariableTable.tables[k].length << std::endl;
            std::cout << "\t\t\tName Index: " << constPoolRef(attr.info.localVariableTable.tables[k].name_index) << std::endl;
            std::cout << "\t\t\tDescriptor Index: " << constPoolRef(attr.info.localVariableTable.tables[k].descriptor_index) << std::endl;
            std::cout << "\t\t\tIndex: " << attr.info.localVariableTable.tables[k].index << std::endl;
        }
    }

    if(typeName == ATT_DEPRECATED){
        std::cout << "\tCP Index: " << constPoolRef((int)attr.attribute_name_index) << std::endl;
        std::cout << "\tLength: " << (int)attr.attribute_length << std::endl;
    }
}
 
std::string ClassPrinter::constPoolRef(u2 index){
    u1 tag = jc.constant_pool[index-1].tag;
    std::string utf8Return = "";
    u4 u4_storage;
    u8 u8_storage;
    
    switch (tag)
    {
        case CONSTANT_Class:
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.classInfo.name_index);
            break;
        case CONSTANT_Fieldref:
            utf8Return += "Field ";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.fieldrefInfo.class_index);
            utf8Return += ".";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.fieldrefInfo.name_and_type_index);
            break;
        case CONSTANT_Methodref:
            utf8Return += "Method ";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.methodrefInfo.class_index);
            utf8Return += ":";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.methodrefInfo.name_and_type_index);
            break;
        case CONSTANT_InterfaceMethodref:
            utf8Return += "Interface ";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.interfaceMethodrefInfo.class_index);
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.interfaceMethodrefInfo.name_and_type_index);
            break;
        case CONSTANT_String:
            utf8Return += "String ";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.stringInfo.string_index);
            break;
        case CONSTANT_Integer:
            utf8Return += "integer ";
            u4_storage = jc.constant_pool[index-1].info.integerInfo.bytes;
            utf8Return += std::to_string( *((int*)&(u4_storage)) );
            break;
        case CONSTANT_Float:
            utf8Return += "float ";
            u4_storage = (jc.constant_pool[index-1].info.floatInfo.bytes);
            utf8Return += std::to_string( *((float*)&u4_storage) );
            break;
        case CONSTANT_Long:
            utf8Return += "long ";
            u8_storage = ((u8)jc.constant_pool[index-1].info.doubleInfo.high_bytes << 32) + jc.constant_pool[index].info.doubleInfo.low_bytes;
            utf8Return += std::to_string( *((long long*)&u8_storage) );
            break;
        case CONSTANT_Double:
            utf8Return += "double ";
            u8_storage = ((u8)jc.constant_pool[index-1].info.doubleInfo.high_bytes << 32) + jc.constant_pool[index].info.doubleInfo.low_bytes;
            if(u8_storage == (u8)0x7ff0000000000000UL)
                utf8Return += "Infinity";
            else if(u8_storage == (u8)0xfff0000000000000UL)
                utf8Return += "-Infinity";
            else if((u8_storage >= (u8)0x7ff0000000000001UL) && (u8_storage <= (u8)0x7fffffffffffffffUL))
                utf8Return += "NaN";
            else if((u8_storage >= (u8)0xfff0000000000001UL) && (u8_storage <= (u8)0xffffffffffffffffUL))
                utf8Return += "NaN";
            else{
                utf8Return += std::to_string( *((double*)&u8_storage) );
            }
            break;
        case CONSTANT_NameAndType:
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.nameAndTypeInfo.name_index);
            utf8Return += ":";
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.nameAndTypeInfo.descriptor_index);
            break;
        case CONSTANT_Utf8:
            utf8Return += getUtf8(index); //utf8Info
            break;
        case CONSTANT_MethodHandle:
            utf8Return += std::to_string((int)jc.constant_pool[index-1].info.methodHandleInfo.reference_kind);
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.methodHandleInfo.reference_index);
            break;
        case CONSTANT_MethodType:
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.methodTypeInfo.descriptor_index);
            break;
        case CONSTANT_InvokeDynamic:
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.invokeDynamicInfo.bootstrap_method_attr_index);
            utf8Return += constPoolRef(jc.constant_pool[index-1].info.invokeDynamicInfo.name_and_type_index);
            break;
        default:
            break;
    }

    return utf8Return;
}
 
int ClassPrinter::verifyAttrType(u2 name_index){
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

std::string ClassPrinter::getUtf8 (u2 name_index){
    cp_info cp_entry;
    u2 length;
    char* name;
    std::string typeName;
 
    // Busca a referência na CP
    cp_entry = jc.constant_pool[name_index-1];
   
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