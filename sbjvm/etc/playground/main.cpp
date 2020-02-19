#include <iostream>
#include <map>

#include <cstdio>
#include <cstdint>

#include "../../include/ClassPrinter.hpp"
#include "../vendor/inih/cpp/INIReader.h"

#include "util.h"

#define TCR_ALL_PASS 0
#define TCR_ASSERTION_FAIL 1
#define TCR_SKIP 2

#define INI_RUNTEST_SEC_NAME "run_tests"

std::unordered_map<u1, instructionInfo> mapInstructions;

INIReader *g_conf_reader;

/**
 * @brief Will check for values read from the constant pool (CP)
 * 
 * This function will print all int, long, float and double constants
 * 
 * Check the docs for more infomation about the CP: https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.4.1
 * 
 * @return int test result
 */
int read_cp_ieee754(){
    if (! g_conf_reader->GetBoolean(INI_RUNTEST_SEC_NAME, __func__, false)){
        return TCR_SKIP;
    }

    ClassPrinter cp;
    JavaClass jc;

    std::string classPath = "java_test";
    std::string classFileName = g_conf_reader->Get(INI_RUNTEST_SEC_NAME, "class_file_name", "");
    if ( classFileName.length() == 0 ){
        printf("(E:%s) You must provide a class file for reading! Aborting test...\n", __func__);
        return TCR_SKIP;
    }

    
    jc.readClassFile(classPath + "/" + classFileName);
    cp.setClass(jc);

    printf("(I) Constant pool size: %hu\n", jc.constant_pool_count);
    u1 tag;
    for (u2 idx = 0; idx < jc.constant_pool_count; idx++){
        tag = jc.constant_pool[idx].tag;
        switch(tag){
            case CONSTANT_Integer:
            case CONSTANT_Float:
                printf("\t[%02hu] %s\n", idx+1, cp.constPoolRef(idx+1).c_str());
                break;
            case CONSTANT_Long:
            case CONSTANT_Double:
                printf("\t[%02hu] %s\n", idx+1, cp.constPoolRef(idx+1).c_str()); idx++;
                break;
            default:
                break;
        }
    }
}

int test_bytecode_impl(){
    if (! g_conf_reader->GetBoolean(INI_RUNTEST_SEC_NAME, __func__, false)){
        return TCR_SKIP;
    }

    // this is a byte operand of an instruction
    u1 byte_op1, byte_op2;
    u4 u4_slot;

    // sign extend test (used in bipush)
    // source: https://stackoverflow.com/a/42536138
    byte_op1 = 0xF0;
    u4_slot = (u4_slot=1u<<(8-1), (byte_op1 ^ u4_slot) - u4_slot);
    printf("Sign-extended: %d (%08lx) of byte value: %02x\n", u4_slot, u4_slot, byte_op1);

    return TCR_ALL_PASS;
}

int main(){

    printf("Please read the " AS_COLOR(TEXT_BOLD, "documentation") " on the %s before viewing results. Thank you.\n", 
        __FILE__
    );

    std::string iniFileName = "conf.ini";
    g_conf_reader = new INIReader(iniFileName);
    if (g_conf_reader->ParseError() < 0) {
        std::cout << "(E) Could not load " << iniFileName << std::endl;
        return -1;
    }

    read_cp_ieee754();
    test_bytecode_impl();
}