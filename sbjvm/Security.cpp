#include "include/Security.hpp"

Security* Security::verifier = NULL;

Security::Security(){}

Security::~Security(){
    free(this->verifier);
}

Security* Security::getInstance(){
    if (!verifier)
        verifier = new Security();
    
    return verifier;
}

bool Security::verifyMagic(u4 magic) const{
    if(magic == 0xCAFEBABE)
        return true;

    return false;
}

bool Security::verifyVersion(u2 version) const{
    if(version >= JAVA && version <= JAVA11)
        return true;
    
    return false;
}

bool Security::verifyClassVersion(u2 minor, u2 major) const{
    if(minor >= JAVA && major <= JAVA7)
        return true;

    return false;
}

bool Security::verifyConstantPoolSize(u2 size) const{
    if(size <= 65535)
        return true;

    return false;
}

bool Security::verifyConstantPoolIndex(u2 index, u2 length) const{
    if(index <= (length-1))
        return true;
    
    return false;
}

bool Security::verifyConstantPoolTag(u1 tag){
    switch(tag){
        case CONSTANT_Utf8: case CONSTANT_Integer: case CONSTANT_Float: 
        case CONSTANT_Long: case CONSTANT_Double: case CONSTANT_Class:
        case CONSTANT_String: case CONSTANT_Fieldref: case CONSTANT_Methodref: 
        case CONSTANT_InterfaceMethodref: case CONSTANT_NameAndType:
        case CONSTANT_MethodHandle: case CONSTANT_MethodType: case CONSTANT_InvokeDynamic:
            return true;
        default:
            return false;
    }
}

bool Security::verifyCodeCPArguments(u1 opcode, u2 arg, cp_info *cp) const{
    if((opcode >= 0x12) && (opcode <= 0x14)){
        // ldc, ldc_w
        if(opcode == 0x12 || opcode == 0x13){
            switch(cp[arg].tag){
                /*
                 * The run-time constant pool entry at index either must be a run-time 
                 * constant of type int or float, or a reference to a string literal,
                 * or a symbolic reference to a class, method type, or method handle.
                 */
                case CONSTANT_Integer: case CONSTANT_Float:
                case CONSTANT_String: case CONSTANT_Class:
                case CONSTANT_MethodType: case CONSTANT_MethodHandle:
                    return true;
                default:
                    return false;
            }
        } else{
            switch(cp[arg].tag){
                /*
                 * The run-time constant pool entry at the index must be a run-time
                 * constant of type long or double.
                 */
                case CONSTANT_Float: case CONSTANT_Double:
                    return true;
                default:
                    return false;
            }
        }
    }
    else if((opcode >= 0xb2) && (opcode <= 0xbb)){
        // getstatic, putstatic, getfield, putfield
        if(opcode >= 0xb2 && opcode <= 0xb5){
            /*
             * The run-time constant pool item at that index must be a symbolic
             * reference to a field (§5.1), which gives the name and descriptor
             * of the field as well as a symbolic reference to the class or interface
             * in which the field is to be found. The referenced field is resolved.
             * 
             * obs1: Putfield precisa de mais checagem?
             * obs2: Verificar como fazer as resoluções.
             */
            if(cp[arg].tag == CONSTANT_Fieldref){
                if(verifySymbolicReference(cp[arg].info.fieldrefInfo.class_index, CONSTANT_Class, cp))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else if(opcode >= 0xb6 && opcode <= 0xb9){
            /*
             * The run-time constant pool item at that index must be a symbolic reference
             * to a method (§5.1), which gives the name and descriptor of the method as well
             * as a symbolic reference to the class in which the method is to be found.
             * The named method is resolved.
             */
            if(cp[arg].tag == CONSTANT_Methodref){
                if(verifySymbolicReference(cp[arg].info.methodrefInfo.class_index, CONSTANT_Class, cp))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else if(opcode == 0xba){
            // Não sei como tratar InvokeDynamic
            return true;
        }
        else{
            /*
             * The run-time constant pool item at the index must be a symbolic reference
             * to a class or interface type.
             */
            if(cp[arg].tag == CONSTANT_Class)
                return true;
            else
                return false;
        }
    }
    else if(opcode == 0xbd){
        if(cp[arg].tag == CONSTANT_Class)
            return true;
        else
            return false;
    }
    else if(opcode == 0xb9){
        /*
         * The run-time constant pool item at that index must be a symbolic reference
         * to an interface method (§5.1), which gives the name and descriptor (§4.3.3) 
         * of the interface method as well as a symbolic reference to the interface in 
         * which the interface method is to be found. The named interface method is resolved.
         */
        if(cp[arg].tag == CONSTANT_InterfaceMethodref){
            if(verifySymbolicReference(cp[arg].info.interfaceMethodrefInfo.class_index, CONSTANT_Class, cp))
                return true;
            else
                return false;
        }
    }
    else if((opcode == 0xc0) && (opcode == 0xc1)){
        /*
         * The run-time constant pool item at the index must be a symbolic reference to
         * a class, array, or interface type.
         */
        if(cp[arg].tag == CONSTANT_Class)
            return true;
        else
            return false;
    }
    else{
        /*
         * he run-time constant pool item at the index must be a symbolic reference to
         * a class, array, or interface type. The named class, array, or interface 
         * type is resolved. 
         */
        if(cp[arg].tag == CONSTANT_Class)
            return true;
        else
            return false;
    }

    return false;
}

bool Security::verifySymbolicReference(u2 index, int type, cp_info *cp) const{
    if(cp[index].tag == type)
        return true;
    
    return false;
}

bool Security::verifySuperClass(u2 index, cp_info *cp){
    /*
     * Check if the index corresponds to a Class entry in the Constant Pool.
     */
    if(index != 0){
        if(verifySymbolicReference(index, CONSTANT_Class, cp))
            return true;
    }
    
    return false;
}