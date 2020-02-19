#pragma once
#include "Types.hpp"
#include <unordered_map>

//! Foward Declaration de JavaClass.
class JavaClass;
//! Foward Declaration de Code_attribute.
struct Code_attribute;
//! Foward Declaration de Exceptions_Attribute.
struct Exceptions_Attribute;

//! Struct que define as tabelas de exceção.
/*!
    Cada entrada do tipo exception_table descreve um <i>handler</i> no array de código.
    A ordem das entradas importa.
    Para saber mais, acesse a documentação da Oracle clicando
    <a href="https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.7.3">aqui</a>.
 */
struct exception_table{
    u2 start_pc;                            //!< Define o início do <i>range</i> do <i>handler</i> da exceção.
    u2 end_pc;                              //!< Define o final do <i>range</i> do <i>handler</i> da exceção.
    u2 handler_pc;                          //!< Define o início da exceção.
    u2 catch_type;                          //!< Se for diferente de 0, deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Class_info. Se for igual a 0, o <i>handler</i> é chamada por todas as exceções. Usado na implementação do <i>finally</i>.
};

//! Struct para definir as classes/interfaces que não pertencem ao <i>package</i>
/*!
    Toda entrada do tipo CONSTANT_Class_info na Constant Pool que represente uma classe ou interface a qual não faz parte do
    package deve conter exatamente uma entrada do tipo struct Classes.
 */
struct Classes {
    u2 inner_class_info_index;              //!< Deve ser uma entrada válida na Constant Pool que representa a classe não pertencente ao package.
    u2 outer_class_info_index;              //!< Se a classe for top-level, ou interface, ou local, ou anônima, então o valor é 0. Caso contrário, é uma entrada válida na Constant Pool do tipo CONSTANT_Class_info que representa a classe ou interface da qual esta classe é membro.
    u2 inner_name_index;                    //!< Se classe for anônima, o valor é 0. Caso contrário, é uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o nome da classe.
    u2 inner_class_access_flags;            //!< Define a flag de acesso da classe.
};

//! Struct que define onde ocorrem as mudanças de linha no arquivo fonte original em relação a um dado ponto do vetor code.
struct line_number_table {   
    u2 start_pc;                            //!< O valor de start_pc indica o índice, no array code, onde o código para uma nova linha começa no arquivo fonte original. 
    u2 line_number;	                        //!< A linha correspondente no arquivo fonte original.
};

//! Struct que define o tamanho do trecho do vetor code onde uma dada variável tem um certo valor.
struct local_variable_table {   
    u2 start_pc;                            //!< Define o ponto no code, a partir do qual, a variável tem um certo valor.
    u2 length;                              //!< Define por quantas posições no vetor code a variável tem um certo valor.
    u2 name_index;                          //!< Define o nome da variável. Deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info.
    u2 descriptor_index;                    //!< Define o tipo da variável. Deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info.
    u2 index;                               //!< Define a posição da variável no vetor de variáveis locais do Frame atual.
};

//! Struct para armazenar referências de Bootstrap Methods
struct bootstrap_methods {
    u2 bootstrap_method_ref;                //!< Entrada válida para Constant Pool do tipo CONSTANT_MethodHandle_info. 
    u2 num_bootstrap_arguments;             //!< Número de argumentos do Bootstrap Method. 
    u2 *bootstrap_arguments;                //!< Deve conter entradas válidas na Constant Pool dos tipos String, Class, Integer, Long, Float, Double, MethodHandle ou MethodType.
};

//! Struct que define o tamanho do trecho do vetor code onde uma dada variável tem um certo valor. Semelhante à struct local_variable_table.
struct local_variable_type_table {   
    u2 start_pc;                            //!< Define o ponto no code, a partir do qual, a variável tem um certo valor.
    u2 length;                              //!< Define por quantas posições no vetor code a variável tem um certo valor.
    u2 name_index;                          //!< Define o nome da variável. Deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info.
    u2 signature_index;                     //!< Define o tipo do Field. Deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info.
    u2 index;                               //!< Define a posição da variável no vetor de variáveis locais do Frame atual.
};

//! Struct que define todos os atributos lidos pela Java Virtual Machine.
/*!
    A struct attribute_info armazena as informações de todos os tipo de atributos reconhecidos por esta Java Virtual Machine.
    Existem alguns tipos que não serão reconhecidos nessa implementação. Para mais informações, acesse a documentação da Oracle clicando
    <a href="https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.7">aqui</a>.
    A implementação, aqui descrita, reconhece atributos os tipos: Constant Value, Code, Exceptions, Inner Classes,
    Enclosing Methods, Signature, Source File, Source Debug Extension, Line Number Table, Local Variable Table,
    Local Variable Type Table e Bootstrap Methods.
 */
struct attribute_info {
    u2 attribute_name_index;                //!< Define o tipo do atributo. Deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info.
    u4 attribute_length;                    //!< Define o tamanho, em bytes, do atributo.

    //! Union para os diferentes tipos de atributos que podem ser armazenados pela Java Virtual Machine.
    union info {
        //! Struct para armazenar um atributo do tipo Constant Value.
        struct ConstantValue_attribute {
            u2 constantvalue_index;         //!< Entrada válida na Constant Pool do tipo Long, Float, Double, Integer ou String.
        } constantValue;

        //! Struct para armazenar um atributo do tipo Code.
        struct Code_attribute {
            u2 max_stack;                   //!< Armazena o tamanho máximo da pilha de operandos do Frame.
            u2 max_locals;                  //!< Armazena o tamanho máximo do array de variáveis locais do Frame.
            
            u4 code_length;                 //!< Armazena o tamanho, em bytes, do código.
            u1 *code;                       //!< Vetor de instruções; Código Java assembly.
            
            u2 exception_table_length;      //!< Armazena o tamanho, em bytes, da tabela de exceções.
            exception_table *tables;        //!< Armazena as tabelas de exceções.

            u2 attributes_count;            //!< Armazena a quantidade de atributos do atributo Code.
            attribute_info *attributes;     //!< Armazena os atributos do atributo Code.
        } code;

        //! Struct para armazenar um atributo do tipo Exceptions.
        struct Exceptions_Attribute {
            u2 number_of_exceptions;        //!< Armazena o número de exceções.
            u2 *exception_index_table;      //!< Armazena is índices das tabelas de exceções.
        } exceptions;

        //! Struct para armazenar um atributo do tipo Inner Classes.
        struct InnerClasses_attribute {
            u2 number_of_classes;           //!< Armazena o número de Inner Classes.
            Classes *classes;               //!< Armazena as informações de cada uma das Inner Classes.
        } innerClasses;

        //! Struct para armazenar um atributo do tipo Enclosing Method.
        struct EnclosingMethod_attribute {
            u2 class_index;                 //!< Entrada válida na Constant Pool do tipo CONSTANT_Class_info que representa a <i>innermost class</i> que encerra a decleração da classe atual.
            u2 method_index;                //!< Se a classe atual não for imediatamente fechada por um método ou contrutor, o valor é 0. Caso contrário, é uma entrada válida na Constant Pool do tipo CONSTANT_NameAndType_info.
        } enclosingMethod;

        //! Struct para armazenar um atributo do tipo Signature.
        struct Signature_attribute {
            u2 signature_index;             //!< Entrada válida na Constant Pool do tipo CONSTANT_Utf8_info.
        } signature;

        //! Struct para armazenar um atributo do tipo Source File.
        struct SourceFile_attribute {
            u2 sourcefile_index;            //!< Entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o nome do arquivo fonte original.
        } sourceFile;

        //! Struct para armazenar um atributo Source Debug Extension.
        struct SourceDebugExtension_attribute {
            u1 *debug_extension;            //!< Armazena informações de debug. Não tem efeitos semânticos na JVM.
        } sourceDebugExtension;

        //! Struct para armazenar um atributo do tipo Line Number Table.
        struct LineNumberTable_attribute {
            u2 line_number_table_length;    //!< Armazena o tamanho do vetor de Line Number Tables.
            line_number_table *tables;      //!< Armazena as tabelas line_number_table.
        } lineNumberTable;

        //! Struct para armazenar um atributo do tipo local variable table.
        struct LocalVariableTable_attribute {
            u2 local_variable_table_length; //!< Armazena o tamanho do vetor de local variable tables.
            local_variable_table *tables;   //!< Armazena as tabelas local_variable_table.
        } localVariableTable;

        //! Struct para armazenar um atributo do tipo local variable type table.
        struct LocalVariableTypeTable_attribute {
            u2 local_variable_type_table_length;    //!< Armazena o tamanho do vetor de local variable type tables.
            local_variable_type_table *tables;      //!< Armazena as tabelas local_variable_type_table..
        } localVariabelTypeTable;

        //! Struct para armazenar um atributo do tipo Bootstrap Methods
        struct BootstrapMethods_attribute {
            u2 num_bootstrap_methods;       //!< Armazena o total de Bootstrap Methods.
            bootstrap_methods *methods;     //!< Armazena os bootstrap_methods.
        } bootstrapMethods;
    } info;
};

//! Armazena as informações sobre os Fields de uma classe Java.
struct field_info {
    u2 access_flags;                        //!< Armazena as flags de acesso.
    u2 name_index;                          //!< Armazena uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o nome do Field.
    u2 type_index;                          //!< Armazena uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o tipo do Field.
    u2 attributes_count;                    //!< Armazena o total de atributos associados a um Field.
    attribute_info *attributes;             //!< Armazena os atributos do Field.
};

//! Armazena as informações sobre os métodos de uma classe Java.
struct method_info {
    u2 access_flags;                        //!< Armazena as flags de acesso.
    u2 name_index;                          //!< Armazena uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o nome do método.
    u2 type_index;                          //!< Armazena uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o tipo do método.
    u2 attributes_count;                    //!< Armazena o total de atributos associados a um método.
    attribute_info *attributes;             //!< Armazena os atributos do método.
};

//! Armazena uma entrada válida na Constant Pool que representa o nome de uma classe Java.
struct CONSTANT_Class_info {
    u2 name_index;                          //!< Entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o nome da classe Java.
};

//! Armazena informações sobre um Field.
struct CONSTANT_Fieldref_info {
    u2 class_index;                         //!< Entrada válida na Constant Pool do tipo CONSTANT_Class_info que representa o nome da classe a qual o Field pertence.
    u2 name_and_type_index;                 //!< Entrada válida na Constant Pool do tipo CONSTANT_NameAndType_info que, quando resolvida, define o nome e o tipo do Field.
};

//! Armazena informações sobre um Method.
struct CONSTANT_Methodref_info {
    u2 class_index;                         //!< Entrada válida na Constant Pool do tipo CONSTANT_Class_info que representa o nome da classe a qual o Method pertence.
    u2 name_and_type_index;                 //!< Entrada válida na Constant Pool do tipo CONSTANT_NameAndType_info que, quando resolvida, define o nome e o tipo do Method.
};

//! Armazena informações sobre um Interface Method.
struct CONSTANT_InterfaceMethodref_info {
    u2 class_index;                         //!< Entrada válida na Constant Pool do tipo CONSTANT_Class_info que representa o nome da classe a qual o Interface Method pertence.
    u2 name_and_type_index;                 //!< Entrada válida na Constant Pool do tipo CONSTANT_NameAndType_info que, quando resolvida, define o nome e o tipo do Interface Method.
};

//! Armazena informações sobre uma String.
struct CONSTANT_String_info {
    u2 string_index;                        //!< Entrada válida na Constant Pool do tipo CONSTANT_Utf8_info que representa o nome da String que deve ser inicializada.
};

//! Armazena infomrções sobre um Integer.
struct CONSTANT_Integer_info {
    u4 bytes;                               //!< Armazena um número inteiro de 32 bits sem sinal.
};

//! Armazena informações sobre um Float.
struct CONSTANT_Float_info {
    u4 bytes;                               //!< Armazena um número de ponto flutuante de 32 bits sem sinal.
};

//! Armazena informações sobre um Long. Cada Long ocupa 2 posições na Constant Pool.
struct CONSTANT_Long_info {
    u4 high_bytes;                          //!< Armazena a parte mais significativa do número Long. Número de 32 bits sem sinal.
    u4 low_bytes;                           //!< Armazena a parte menos significativa do número Long. Número de 32 bits sem sinal.
};

//! Armazena informações sobre um Double. Cada Long ocupa 2 posições na Constant Pool.
struct CONSTANT_Double_info {
    u4 high_bytes;                          //!< Armazena a parte mais significativa do número Double. Número de 32 bits sem sinal.
    u4 low_bytes;                           //!< Armazena a parte menos significativa do número Double. Número de 32 bits sem sinal.
};

//! Armazena informações de nome e tipo sobre Fields, Methods e Interface Methods.
struct CONSTANT_NameAndType_info {
    u2 name_index;                          //!< Entrada válida para Constant Pool do tipo CONSTANT_Utf8_info. Representa o nome de um Field, Method ou Interface Method.
    u2 descriptor_index;                    //!< Entrada válida para Constant Pool do tipo CONSTANT_Utf8_info. Representa o tipo de um Field, Method ou Interface Method.
};

//! Armazena informações sobre várias das estruturas da classe Java.
struct CONSTANT_Utf8_info {
    u2 length;                              //!< Determina o tamanho do vetor de bytes.
    u1 *bytes;                              //!< Vetor de bytes que formam uma String.
};

//! Armazena informações sobre um Method Handle.
struct CONSTANT_MethodHandle_info {
    u1 reference_kind;                      //!< Armazena um valor entre 1 e 9. O valor representa o tipo de Method Handle.
    u2 reference_index;                     //!< Entrada válida na Constant Pool. Se o número reference_kind estiver entre 1 e 4, a entrada deve ser do tipo CONSTANT_Fieldref_info. Se o número for entre 5 e 8, deve ser do tipo CONSTANT_Methodref_info. Se o número for 9, deve ser do tipo CONSTANT_InterfaceMethodref_info.
};

//! Armazena informações sobre o tipo de um Method.
struct CONSTANT_MethodType_info {
    u2 descriptor_index;                    //!< Entrada válida na Constant Pool do tipo CONSTANT_Utf8_info. Define o tipo do Method.
};

//! Armaena informações para serem utilizadas pela instrução <i>invokedynamic</i>.
struct CONSTANT_InvokeDynamic_info {
    u2 bootstrap_method_attr_index;         //!< Entrada válida no array do atributo Bootstrap Methods da classe.
    u2 name_and_type_index;                 //!< Entrada válida na Constant Pool do tipo CONSTANT_NameAndType_info, quando resolvidas, definem o nome e o tipo do Method.
};

//! Armazena todas as informações da Constant Pool de uma classe Java.
struct cp_info {
    u1 tag;                                 //!< Armazena um valor que identifica o tipo da estrutura armazenada pela union.

    //! Union que armazena todos os tipos de estruturas sobre a classe Java.
    union info {
        CONSTANT_Class_info classInfo;                              //!< Armazena uma CONSTANT_Class_info.
        CONSTANT_Fieldref_info fieldrefInfo;                        //!< Armazena uma CONSTANT_Fieldref_info.
        CONSTANT_Methodref_info methodrefInfo;                      //!< Armazena uma CONSTANT_Methodref_info.
        CONSTANT_InterfaceMethodref_info interfaceMethodrefInfo;    //!< Armazena uma CONSTANT_InterfaceMethodref_info.
        CONSTANT_String_info stringInfo;                            //!< Armazena uma CONSTANT_String_info.
        CONSTANT_Integer_info integerInfo;                          //!< Armazena uma CONSTANT_Integer_info.
        CONSTANT_Float_info floatInfo;                              //!< Armazena uma CONSTANT_Float_info.
        CONSTANT_Long_info longInfo;                                //!< Armazena uma CONSTANT_Long_info.
        CONSTANT_Double_info doubleInfo;                            //!< Armazena uma CONSTANT_Double_info.
        CONSTANT_NameAndType_info nameAndTypeInfo;                  //!< Armazena uma CONSTANT_NameAndType_info.
        CONSTANT_Utf8_info utf8Info;                                //!< Armazena uma CONSTANT_Utf8_info.
        CONSTANT_MethodHandle_info methodHandleInfo;                //!< Armazena uma CONSTANT_MethodHandle_info.
        CONSTANT_MethodType_info methodTypeInfo;                    //!< Armazena uma CONSTANT_MethodType_info.
        CONSTANT_InvokeDynamic_info invokeDynamicInfo;              //!< Armazena uma CONSTANT_InvokeDynamic_info.
    } info;
};

//! Define a estrutura de uma classe Java.
struct JavaClassFileFormat {
    //! Armazena o Magic do .class.
    /*!
      O item magic fornece o número mágico que identifica o formato de arquivo class;
      Tem valor igual a 0xCAFEBABE.
    */
    u4 magic;
    
    //! Armazena a Minor Version do .class.
    /*!
      O valor de minor_version corresponde a menor versão da JVM necessária para rodar esse arquivo class.
    */
    u2 minor_version;
    //! Armazena a Major Version do .class.
    /*!
      O valor de major_version corresponde a maior versão da JVM que consegue para rodar esse arquivo class.
    */
    u2 major_version;

    //! Armazena a quantidade de itens na Constant Pool.
    /*!
      O valor de constant_pool_count contém a quantidade de entradas válidas na Constant Pool. Cada entrada
      aumenta seu tamanho em 1, com exceção das entradas Long e Double que aumentam seu tamanho em 2.
      O valor máximo de constant_pool_count é igual a 65535.
    */
    u2 constant_pool_count;
    //! Armazena os dados da Constant Pool.
    /*!
      A constant_pool é uma tabela de estruturas representando várias strings constantes, nomes de classes e interfaces,
      nomes de fields, e outras constantes que são referenciadas dentro da estrutura do ClassFile e suas subestruturas.
      O formato de cada entrada na tabela constant_pool é indicado pelo seu primeiro byte "tag".
      É indexado a partir de 1 até constant_pool_count - 1.
    */
    cp_info *constant_pool;

    //! Armazena a flag de acesso do ClassFile.
    /*!
      O valor de access_flags é uma máscara de flags usadas para denotar permissões de acesso e propriedades da classe ou interface.
      A interpretação de cada flag, quando setada, é mostrada abaixo:
      <table>
        <tr>
            <th>Nome da Flag</th>
            <th>Valor</th>
            <th>Interpretação</th>
        </tr>
        <tr>
            <td>ACC_Public</td>
            <td>0x0001</td>
            <td>
                Declarado público; Pode ser acessado de fora do seu pacote.
            </td>
        </tr>
        <tr>
            <td>ACC_FINAL</td>
            <td>0x0010</td>
            <td>
                Declarado final; Não pode conter subclasses.
            </td>
        </tr>
        <tr>
            <td>ACC_SUPER</td>
            <td>0x0020</td>
            <td>
                Trate métodos de superclasses de maneira especial quando invocados pela instrução
                <i>invokespecial</i>
            </td>
        </tr>
        <tr>
            <td>ACC_INTERFACE</td>
            <td>0x0200</td>
            <td>
                É uma interface, não uma classe.
            </td>
        </tr>
        <tr>
            <td>ACC_ABSTRACT</td>
            <td>0x0400</td>
            <td>
                Declarado abstrato; Não deve ser instânciado.
            </td>
        </tr>
        <tr>
            <td>ACC_SYNTHETIC</td>
            <td>0x1000</td>
            <td>
                Declarado sintático; Não aparece no código fonte.
            </td>
        </tr>
        <tr>
            <td>ACC_ANNOTATION</td>
            <td>0x2000</td>
            <td>
                Declarado como um tipo Annotation.
            </td>
        </tr>
        <tr>
            <td>ACC_ENUM</td>
            <td>0x4000</td>
            <td>
                Declarado como um tipo Enum.
            </td>
        </tr>
    </table>
    */
    u2 access_flags;
    //! Representa a classe ou interface definida por esse arquivo .class.
    /*!
      O valor de this_class deve ser uma entrada válida na Constant Pool do tipo CONSTANT_Class_info
      que representa a classe ou interface definida por esse arquivo .class.
    */
    u2 this_class;
    //! Armazena a classe a qual a classe desse arquivo herda.
    /*!
      O valor de super_class deve ser "0" ou uma entrada válida na Constant Pool. Caso o valor seja "0",
      isso implica que a classe não herda de nenhuma outra classe e, portanto, trata-se da classe Object.
      Caso contrário, a entrada na Constant Pool deve ser do tipo CONSTANT_Class_info e representa a classe
      a qual a classe, definida nesse arquivo, herda.
    */
    u2 super_class;

    //! Armazena a quantidade de superinterfaces dessa classe ou interface.
    u2 interfaces_count;
    //! Armazena as entradas na Constant Pool que definem as superinterfaces dessa classe ou interface
    /*!
      Cada valor armazenado deve ser uma entrada válida na Constant Pool, e deve ser do tipo CONSTANT_Class_info,
      representam as superinterfaces dessa classe ou interface, aparecendo na ordem da esquerda para direita dada
      no arquivo do código fonte.
    */
    u2* interfaces;             // interfaces[interfaces_count]

    //! Armazena a quantidade de fields dessa classe ou interface.
    u2 fields_count;
    //! Armazena os Fields associados a essa classe ou interface.
    /*!
      Cada entrada no vetor fields[] deve ser do tipo field_info. A estrutura representa todos os fields, tanto variáveis
      da classe quanto variáveis de instância. Não contém fields que são herdados de superclasses ou superinterfaces.
    */
    field_info *fields;         // fields[fields_count]

    //! Armazena a quantidade de methods definidos nessa classe.
    u2 methods_count;
    //! Armazena os Methods associados a essa classe ou interface.
    /*!
      Cada entrada no vetor methods[] deve ser do tipo method_info. A estrutura representa todos os methods declarados por
      essa classe ou interface, incluindo instance methods, class methods, instance initialization methods, e qualquer class
      ou interface initialization methods. Não contém methods que são herdados de superclasses ou superinterfaces.
    */
    method_info *methods;       // methods[methods_count]

    //! Armazena a quantidade de atributos associados a essa classe.
    u2 attributes_count;
    //! Armazena os Attributes associados a essa classe.
    /*!
      Cada entrada no vetor attributes[] deve ser do tipo attribute_info. A estrutura representa todos os attributes declarados
      nessa classe. Os tipos lidos por essa JVM podem ser vistos na tabela contida em JavaClass::setAttribute(attribute_info *attr).
    */
    attribute_info *attributes; // attributes[attributes_count]
} ;