#pragma once

/*! \enum MethodAcessFlags
    \brief 
*/
typedef enum {
    ACC_PUBLIC =        0x0001, // Define o acesso publico
    ACC_PRIVATE =       0x0002, // Define um Field privado; Apenas a classe acessa.
    ACC_PROTECTED =     0x0004, // Define um Field protegido; Subclasses acessam.
    ACC_STATIC =        0x0008, // Define um Field estático; Pode ser referenciado sem instância da classe
    ACC_FINAL =         0x0010, // Define que não podem haver subpacotes; Nunca atribuído após a construção
    ACC_SUPER =         0x0020, // Define a Super Class
    ACC_VOLATILE =      0x0040, // Define um Field volátil; Não pode ser posto em "cache"
    ACC_TRANSIENT =     0x0080, // Define um Field transiente; Não pode ser persistido
    ACC_INTERFACE =     0x0200, // Define uma Interface
    ACC_ABSTRACT =      0x0400, // Define um Abstract
    ACC_SYNTHETIC =     0x1000, // Define um Synthetic, não presente no código-fonte
    ACC_ANNOTATION =    0x2000, // Define uma Annotation
    ACC_ENUM =          0x4000  // Define um tipo Enum
} MethodAccessFlag;

// Flags para definição dos Methods!
#define ACC_SYNCHRONIZED    0x0020      // Define um método synchronized (uso de monitor)
#define ACC_BRIDGE          0x0040      // Define um método bridge
#define ACC_VARARGS         0x0080      // Define um método com número variável de argumentos
#define ACC_NATIVE          0x0100      // Define um método nativo; implementado em outra linguagem
#define ACC_STRICT          0x0800      // Define strictfp; floating-point apenas.

// Constant Pool Types
#define CONSTANT_Class              7   //!< CONSTANT_Class_info tag
#define CONSTANT_Fieldref           9   //!< CONSTANT_Fieldref_info tag
#define CONSTANT_Methodref          10  //!< CONSTANT_Methodref_info tag
#define CONSTANT_InterfaceMethodref 11  //!< CONSTANT_InterfaceMethodref_info tag
#define CONSTANT_String             8   //!< CONSTANT_String_info tag
#define CONSTANT_Integer            3   //!< CONSTANT_Integer_info tag
#define CONSTANT_Float              4   //!< CONSTANT_Float_info tag
#define CONSTANT_Long               5   //!< CONSTANT_Long_info tag
#define CONSTANT_Double             6   //!< CONSTANT_Double_info tag
#define CONSTANT_NameAndType        12  //!< CONSTANT_NameAndType_info tag
#define CONSTANT_Utf8               1   //!< CONSTANT_Utf8_info tag
#define CONSTANT_MethodHandle       15  //!< CONSTANT_MethodHandle_info tag
#define CONSTANT_MethodType         16  //!< CONSTANT_MethodType_info tag
#define CONSTANT_InvokeDynamic      18  //!< CONSTANT_InvokeDynamic_info tag

// Java Versions
#define JAVA    0
#define JAVA1_2 46              //!< Java 1.2 Version
#define JAVA1_3 47              //!< Java 1.3 Version
#define JAVA1_4 48              //!< Java 1.4 Version
#define JAVA5   49              //!< Java 5 Version
#define JAVA6   50              //!< Java 6 Version
#define JAVA7   51              //!< Java 7 Version
#define JAVA8   52              //!< Java 8 Version
#define JAVA9   53              //!< Java 9 Version
#define JAVA10  54              //!< Java 10 Version
#define JAVA11  55              //!< Java 11 Version

// Attribute Types
#define ATT_CONST_VALUE     1   //!< Constant Value Attribute Value
#define ATT_CODE            2   //!< Code Attribute Value
#define ATT_STACK_MAP_TABLE 3   //!< Stack Map Map Table Attribute Value
#define ATT_EXCEPTIONS      4   //!< Exceptions Attribute Value
#define ATT_INNER_CLASSES   5   //!< Inner Classes Attribute Value
#define ATT_ENCLO_METHOD    6   //!< Enclosing Methods Attribute Value
#define ATT_SYNTHETIC       7   //!< Synthetic Attribute Value
#define ATT_SIGNATURE       8   //!< Signature Attribute Value
#define ATT_SRC_FILE        9   //!< Source File Attribute Value
#define ATT_SRC_DBG_EXT     10  //!< Source Debug Extension Attribute Value
#define ATT_LINE_NUM_TABLE  11  //!< Line Number Table Attribute Value
#define ATT_LOCAL_VAR_TABLE 12  //!< Local Variable Table Attribute Value
#define ATT_LCL_VAR_T_TABLE 13  //!< Local Variable Type Table Attribute Value
#define ATT_DEPRECATED      14  //!< Deprecated Attribute Value
#define ATT_RT_V_ANNOT      15  //!< Runtime Visible Annotations Attribute Value
#define ATT_RT_IN_ANNOT     16  //!< Runtime Invisible Annotations Attribute Value
#define ATT_RT_V_P_ANNOT    17  //!< Runtime Visible Parameter Annotations Attribute Value
#define ATT_RT_IN_P_ANNOT   18  //!< Runtime Invisible Parameter Annotations Attribute Value
#define ATT_ANNOT_DEFAULT   19  //!< Annotation Default Attribute Value
#define ATT_BOOT_METHOD     20  //!< Bootstrap Methods Attribute Value