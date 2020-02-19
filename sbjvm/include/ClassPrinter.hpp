#include "JavaClass.hpp"

/*! \class ClassPrinter ClassPrinter.hpp "ClassPrinter.hpp"
 *  \brief Classe responsável por printar todo o Bytecode
 * 
 * A classe ClassPrinter é a classe responsável pela impressão do Bytecode.
 * Após a leitura, alocação e armazenamento das informações do arquivo .class
 * pela classe JavaClass, os métodos contidos nessa classe irão exibir no terminal
 * todas as informações que seriam mostradas em um BytecodeViewer.
 * 
 */
class ClassPrinter {
    public:
        ClassPrinter();
        ~ClassPrinter();

        void setClass(JavaClass);

        // Funções Bytecode Viewer
        void printClassFile();                      // Bytecode viewer
        void printVersion(u2, u2);                  // Print Minor e Major version
        void printConstPool();                      // Print da Constant Pool
        void printAttribute(attribute_info);        // Printa os atributos
        std::string constPoolRef(u2);
        std::string getUtf8 (u2 name_index);
        int verifyAttrType(u2);                     // Verifica o tipo do atributo sendo alocado
    
    private:
        JavaClass jc;                               //!< Armazena uma cópia da classe Java carregada.
};

/** \fn ClassPrinter::ClassPrinter()
 *  \brief Construtor padrão da classe.
 */

/** \fn ClassPrinter::~ClassPrinter()
 *  \brief Destrutor padrão da classe.
 */

/** \fn void ClassPrinter::setClass(JavaClass)
 *  \brief Métoro que armazena uma cópia do .class carregado.
 * 
 *  O método setClass(JavaClass jc) é responsável por receber a classe que foi carregada
 *  a partir do .class, e armazenar uma cópia na classe ClassPrinter que será utilizada para
 *  exibir o Bytecode lido.
 *  
 *  \param jc; Cópia do .class .
 *  \return Nada é retornado.
 */

/** \fn void ClassPrinter::printClassFile()
 *  \brief Método base para impressão do Bytecode do classe Java.
 * 
 *  O método printClassFile() é a base do exibidor do Bytecode. Aqui serão impressas as informações
 *  base da classe - tais como flag de acesso, nome da classe, nome da super classe, contagem de
 *  interfaces, fields, methods e attributes, as interfaces, os fields e os methods - e irá chamar
 *  outro método para imprimir o resto das informações - attributes.
 *  
 *  \return Não retorna nada.
 */

/** \fn void ClassPrinter::printVersion(u2, u2)
 *  \brief Método responsável pela impressão das versões.
 * 
 *  O método recebe as minor e major versions da classe Java carregada e, imprime para o usuário
 *  qual a menor e a maior versão da Java Virtual Machine necessária para executar a classe Java.
 *  
 *  \param minor; Valor da minor_version da classe Java carregada;
 *  \param major; Valor da major_version da classe Java carregada;
 *  \return Não retorna nada.
 */

/** \fn void ClassPrinter::printConstPool()
 *  \brief Método responsável por imprimir a Constant Pool.
 * 
 *  O método printConstPool() é responsável por imprimir toda a Constante Pool da classe Java
 *  carregada. O método tem como propósito principal a verificação do conteúdo carregado do
 *  arquivo .class e não deve estar presente na versão de produção da Java Virtual Machine.
 * 
 *  \return Não retorna nada.
 */

/** \fn void ClassPrinter::printAttribute(attribute_info)
 *  \brief Método responsável por imprimir um atributo.
 * 
 *  O método printAttribute(attribute_info attr) é responsável por imprimir um dado atributo
 *  - passado como parâmetro. Como existem atributos que contém atributos (Code_attribute), a
 *  função permite a chamada recursiva para que vários atributos sejam impressos "simultâneamente". 
 * 
 *  \param attr; Recebe um attribute_info para ser impresso.
 *  \return Não retorna nada.
 */

/** \fn std::string ClassPrinter::constPoolRef(u2)
 *  \brief Método responsável por resolver as referências à Constant Pool.
 * 
 *  O método constPoolRef(u2 index) recebe uma entrada válida para a Constant Pool e, a partir
 *  dessa entrada, é capaz de resolver as referências até que se chegue em uma entrada do tipo
 *  CONSTANT_Utf8_info, imprimindo a mesma.
 * 
 *  \param index; Recebe uma entrada válida para Constant Pool.
 *  \return Retorna uma string contida em uma entrada CONSTANT_Utf8_info da Constant Pool.
 */

/** \fn std::string ClassPrinter::getUtf8(u2)
 *  \brief Método responsável por transformar o vetor UTF8 em uma std::string.
 * 
 *  O método getUtf8(u2 name_index) recebe uma entrada válida na Constant Pool do tipo CONSTANT_Utf8_info
 *  e converte o vetor de caracteres UTF8 em uma std::string.
 * 
 *  \param name_index; Recebe uma entrada válida para Constant Pool.
 *  \return Retorna uma string contida em uma entrada CONSTANT_Utf8_info da Constant Pool.
 */

/** \fn int ClassPrinter::verifyAttrType(u2)
 *  \brief Método responsável por retornar o tipo de um atributo.
 * 
 *  O método verifyAttrType(u2 name_index) deve receber uma entrada válida na Constant Pool do tipo
 *  CONSTANT_Utf8_info, verifica o tipo de atributo contido no vetor de caracteres da entrada e,
 *  com base no conteúdo do vetor, retorna um número de 1 a 20 para cada um dos tipos de atributos
 *  possíveis. Os tipos de atributos podem ser verificados clicando
 *  <a href="https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.7" target="_blank">aqui</a>.
 * 
 *  \param name_index; Recebe uma entrada válida para Constant Pool do tipo CONSTANT_Utf8_info.
 *  \return Retorna um valor entre 1 e 20 para cada tipo de atributo reconhecido pela JVM.
 */