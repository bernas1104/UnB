#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Types.hpp"
#include "Constants.hpp"
#include "Structs.hpp"
#include "AssemblyMap.hpp"
#include "Security.hpp"

/*! \class JavaClass JavaClass.hpp "JavaClass.hpp"
 *  \brief Define o formato e os métodos do Class Loader da JVM.
 *  \extends JavaClassFileFormat
 * 
 * A classe JavaClass contém as structs e métodos necessários para
 * implementação do Class Loader da JVM. Aqui os arquivos ".class"
 * necessários serão carregados, a medida que forem necessários -
 * carregador dinâmico -, lidos e as estruturas - como class heap,
 * constant pool e etc... - serão lidas e alocadas.
 * 
 */
class JavaClass : public JavaClassFileFormat {
    public:
        JavaClass();
        bool readClassFile(std::string className);  // Lê o .class
        
        // Finalizar o programa
        void deleteBytecode();                      // Desaloca o Bytecode
        void deleteConstantPool();                  // Desaloca a Constant Pool
        void deleteClassInfo();                     // Desaloca Interfaces, Métodos e Fields
        void deleteAttributes(attribute_info);      // Desaloca Atributos

    private:
        //! Armazena o Bytecode do arquivo .class sendo carregado para exibição/interpretação.
        bytecode *bytes;                            // Bytecode do .class
        //! Armazena o tamanho do Bytecode.
        int bcSize;                                 // Tamanho do Bytecode
        //! Armazena o index atual do Bytecode.
        int bytecode_index;                         // Index atual do bytecode

        // Manipulação do Bytecode
        void insertByte(u1 byte);                   // Insere todos os bytes
        u1 getByte(int nByte);                      // Busca o N-ésimo byte do Bytecode
        
        // Construção da Constant Pool
        void setClassMagic();                       // Define/Verifica o MAGIC
        void setVersions(int);                      // Define Minor/Major Version
        void setCPCount();                          // Define o tamanho da CP
        bool verifyTag(u1 tag);                     // Verifica se a Tag é válida
        void setConstantPool();                     // Aloca e constrói a CP
        int getCPSize();                            // Devolve a extensão da CP

        // Construção da Class
        void setClassInfo();
        void setInterfaces();                       // Define as Interfaces (CP)
        void setFields();                           // Define os Fields do .class
        void setMethods();                          // Define os Methods do .class
        void setAttribute(attribute_info*);         // Seta de acordo com o tipo, devolve attr

    public:
        //! Armazena o path da classe carregada
        std::string classFilePath;

        // Utilities
        int verifyAttrType(u2);                             // Verifica o tipo do atributo sendo alocado
        std::string getUtf8(u2);                            // Gera uma string com base em um vetor de bytes.
        bool isMethodAccessFlagSet(u2, MethodAccessFlag);   // Verifica se uma flag de um método está habilitada
};

/** \fn JavaClass::JavaClass()
 *  \brief Método construtor da classe "JavaClass"
 * 
 *  Construtor padrão. O método inicia todos os atributos de instância da classe para
 *  os valores "0" ou "nullptr", a fim de evitar problemas de valores lixo ao realizar
 *  as operações de leitura e alocação dos arquivos ".class".
 */

/** \fn void JavaClass::readClassFile(std::string className)
 *  \brief Método para leitura do ".class"
 * 
 *  O método readClassFile(std::string className) é responsável por realizar a leitura
 *  de um arquivo ".class" - determinado pelo parâmetro className - e calcular o tamanho
 *  do arquivo ao mesmo tempo em que realiza a leitura.
 *  Para cada byte lido do arquivo, o método realiza uma chamada para o método
 *  JavaClass::insertByte(u1 byte) para que o byte seja inserido em uma lista encadeada
 *  quer será alocada para guardar os bytes do arquivo.
 * 
 *  \param className é uma string com o nome do ".class" sendo lido.
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::deleteBytecode()
 *  \brief Método que deleta o ".class" da memória.
 * 
 *  Após a leitura do ".class", execução dos métodos e alocação dos dados na Heap,
 *  a lista encadeada deve ser desalocada da memória, pois já não tem mais utilidade.
 *  Dessa maneira, o método deleteBytecode() percorre a lista encadeada que contém os
 *  bytes lidos do ".class" e, um a um, libera o dado da memória.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::deleteConstantPool()
 *  \brief Método que deleta a Constant Pool da memória.
 * 
 *  Após o término da execução do programa pela JVM, os dados devem ser desalocados
 *  da memória. O método deleteConstantPool() é responsável por desalocar os dados
 *  da Constant Pool, alocados durante a fase de load do programa.
 *  A Constant Pool é alocada como um vetor que contém um segundo vetor com as informações
 *  relativas a cada um dos tipos de constante possíveis. Dessa forma, a função percorre
 *  cada uma das constantes alocadas, liberando o vetor de informações alocada para cada uma
 *  e, por fim, desaloca o vetor da Constant Pool da memória.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::deleteClassInfo()
 *  \brief Método que desaloca o restante das informçaões sobre a classe da memória.
 * 
 *  Após o término da execução do programa pela JVM, e após a liberação da Constant Pool, é
 *  necessário desalocar o restante das informações sobre a classe da memória. Entre essas
 *  informações estão: interfaces, fields, methods e attributes.
 *  No caso específico dos attributes, uma segunda função é chamada para lidar com a desalocação
 *  desses dados da memória.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::deleteAttributes(attribute_info attr)
 *  \brief Método que desaloca atributos com alocação dinâmica em sua composição.
 * 
 *  Alguns atributos da JVM possuem vetores em sua implementação e estes por sua vez são alocados
 *  dinâmicamente e, portanto, precisam ser liberados ao final da execução.
 *  O método verifica, com base no campo attribute_info::attribute_name_index, o tipo do atributo
 *  sendo desalocado. Apenas três casos são tratados por esse método, quais sejam: Code, Inner Class
 *  e Line Number Table.
 *  No caso do atributo Code, pode ser necessário uma chamada recursiva para liberação de atributos
 *  associados a ele.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::insertByte(u1 byte)
 *  \brief Método responsável por inserir os bytes do ".class" em uma lista encadeada
 * 
 *  Ao iniciar a leitura do arquivo ".class", a função insertByte(u1 byte) recebe o byte
 *  sendo atualmente lido como parâmetro e o insere em uma lista encadeada, definida pela
 *  struct bytecode.
 *  A ideia é não precisar se preocupar com o tamanho de cada ".class" sendo lido, uma vez
 *  que a lista encadeada é uma estrutura de alocação dinâmica.
 *  Após a conclusão da execução do programa Java, a lista encadeada deve ser liberada da
 *  memória, o que ocorre pela execução do método JavaClass::deleteBytecode().
 * 
 *  \param byte é um tipo especial definido como um unsigned char.
 *  \return Nada é retornado.
 */

/** \fn u1 JavaClass::getByte(int nByte)
 *  \brief O método recebe um número, nByte, e retorna o n-ésimo byte da lista encadeada.
 * 
 *  Quando um ".class" precisa ser carregado, para posterior execução, precisamos ler os
 *  bytes para uma lista encadeada - utilizando a função JavaClass::insertByte(u1 byte) -
 *  e, após a leitura, precisamos acessar os bytes, alocados em memória, para composição
 *  das estrturas da classe Java.
 *  O método irá receber, como parâmetro, um índice que determina qual byte deve ser lido,
 *  percorre a lista de bytes, até que o número procurado seja encontrado, e retorna o
 *  byte para utiilzação.
 * 
 *  \param nByte; Integer que determina qual byte, da lista encadeada, será lido.
 *  \return Retorna um byte sem consideração de sinal.
 */

/** \fn bool JavaClass::setClassMagic()
 *  \brief Método responsável por verificar e setar o Magic
 * 
 *  Todo arquivo ".class" possui, em seu inicio, 4 bytes que formam o seu Magic. O método
 *  setClassMagic() seta e verifica se o Magic do arquivo sendo lido é correto, retornando
 *  "True" caso seja correto, e "False" caso seja incorreto.
 *  O método executa a leitura de um byte por vez e, para cada byte, realiza uma operação
 *  de shift left de 24, 16, 8 e 0 bits respectivamente. Ao final, o número obtidido, em
 *  hexadecimal, deve ser igual a 0xCAFEBABE.
 * 
 *  \return Retorna "True" ou "False" de acordo com a
 *  validade do magic lido.
 */

/** \fn void JavaClass::setVersions(int byte)
 *  \brief Método responsável por setar as versões Minor e Major.
 * 
 *  Todo arquivo ".class" possui uma versão Minor (m) e Major (M). Juntas, elas formam
 *  a versão do ".class". A implementação da JVM poderá rodar programas Java que estejam
 *  em um limite contínuo determinado por n <= v <= M.
 *  Como o começo dos arquivos ".class" são iguais, os índices dos bytes que determinam
 *  as versões minor e major são: 4 e 5 (Minor Version), 6 e 7 (Major Version). Dessa forma,
 *  o método recebe um arquivo, byte, que irá determinar o primeiro byte a ser lido de cada
 *  versão, 4 e 6 respectivamente, e, de acordo com o número, irá associar o número calculado
 *  aos atributos minor_version ou major_version.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::setCPCount()
 *  \brief Método determina a quantidade de entradas na Constant Pool
 * 
 *  Após a leitura do Magic, Minor e Major, deve-se estabelecer o tamanho da Constant Pool.
 *  Assim como os dados já lidos, a posição dos bytes que determinam a quantidade de entradadas 
 *  da Constant Pool é fixo. Dessa forma, lê-se os bytes 8 e 9 da lista encadeada para determina
 *  essa quantidade. Após a leitura e cálculo do número - utilizando shift left - o número é salvo
 *  no atributo constant_pool_count.
 * 
 *  \return Nada é retornado
 */

/** \fn bool JavaClass::verifyTag(u1 tag)
 *  \brief Método responsável por verificar se a tag da constante sendo lida é válida.
 * 
 *  Para cada constante da Constant Pool existe uma tag associada, que determina o tipo da constante
 *  salvo na n-ésima entrada da tabela.
 *  As tags válidas são exibidas abaixo:
 *  
 *  <table>
 *      <tr>
 *          <th>Tipo de constante</th>
 *          <th>Valor</th>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Class</td>
 *          <td>7</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Fieldref</td>
 *          <td>9</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Methodref</td>
 *          <td>10</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_InterfaceMethodref</td>
 *          <td>11</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_String</td>
 *          <td>8</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Integer</td>
 *          <td>3</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Float</td>
 *          <td>4</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Long</td>
 *          <td>5</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Double</td>
 *          <td>6</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_NameAndType</td>
 *          <td>12</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_Utf8</td>
 *          <td>1</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_MethodHandle</td>
 *          <td>15</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_MethodType</td>
 *          <td>16</td>
 *      </tr>
 *      <tr>
 *          <td>CONSTANT_InvokeDynamic</td>
 *          <td>18</td>
 *      </tr>
 *  </table>
 * 
 *  Caso a tag lida seja igual a qualquer um dos números descritos acima, o valor "True" é
 *  retornado e, portanto, a tag é válida. Caso contrário, o valor "False" é retornado e temos
 *  uma tag inválida sendo lida.
 * 
 *  \param tag; Byte sem sinal que contém a tag da constante sendo lida.
 *  \return Retorna "True" ou "False" de acordo com a
 *  validade da tag lida.
 */

/** \fn void JavaClass::setConstantPool()
 *  \brief Método responsável por montar a Constant Pool
 *  
 *  Após a leitura da quantidade de entradas da Constant Pool, deve-se monta-la. Para iniciar
 *  a sua construção, devemos alocar - em formato de vetor - uma quantidade X de entradas na
 *  tabela (onde X é determinado pela função JavaClass::setCPCount()). Após a alocação, inicia-se
 *  a leitura das entradas da tabela.
 *  Como existem 14 tipos diferentes de constantes, deve-se analisar - por meio da leitura
 *  inicial da tag - qual tipo de constante está sendo atualmente lida. Após a determinação
 *  do tipo de constante, iremos alocar a quantidade necessária de memória para aquele dado
 *  tipo e, por fim, associa-lo a n-ésima entrada da Constant Pool.
 * 
 *  \return Nada é retornado
 */

/** \fn void JavaClass::setCPConstant(int cp_index, int size, int byteIndex)
 *  \brief Método responsável por atribuir uma constante à Constant Pool.
 * 
 *  O método setCPConstant(int cp_index, int size, int byteIndex) recebe como argumentos:
 *  o número da entrada na tabela (cp_index), o tamanho total que precisa ser alocado (size) e
 *  qual o byte sendo lido da lista encadeada (byteIndex).
 *  A partir desses parâmetros, o método irá alocar o espaço necessário em formato de vetor e
 *  irá atribuir, para cada posição do vetor, um byte lido da lista encadeada, até que seja lido
 *  uma quantidade igual ao tamanho incialmente alocado.
 * 
 *  \param cp_index; Integer que aponta para uma posição da Constant Pool.
 *  \param size; Integer que determina o tamanho da constante sendo alocada.
 *  \para byteIndex; Integer que aponta para o byte sendo lido no bytecode.
 *  \return Nada é retornado.
 */

/** \fn int JavaClass::getCPSize()
 *  \brief Método que calcula a quantidade de bytes que contém a Constant Pool
 * 
 *  Após a leitura da quantidade de entradas e da montagem da tabela da Constant
 *  Pool, é necessário, antes de continuar a alocação do ".class", determinar quantos
 *  bytes formam a Constant Pool. Como cada ".class" possui números e tipos diferentes
 *  de dados na tabela, é necessário calcular a quantidade de bytes que compõe todos os
 *  dados da tabela para, a partir disso, ter o número do primeiro byte após a tabela
 *  e ser possível continuar a leitura correta dos dados da classe Java.
 * 
 *  \return Retorna o tamanho, em Integer, da Constant Pool.
 */

/** \fn void JavaClass::setClassInfo()
 *  \brief Método responsável por setar as flags, métodos e atributos da classe.
 * 
 *  O método setClassInfo() é responsável por setar as seguintes informações:
 *  <table>
 *      <tr>
 *          <th>Campo</th>
 *          <th>Descrição</th>
 *      </tr>
 *      <tr>
 *          <td>Acess Flag</td>
 *          <td>
 *              Define o acesso da classe. Pode ser:
 *              Public, Final, Super, Interface, Abstract, Synthectic, Annotation e Enum
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>This Class</td>
 *          <td>
 *              Aponta para um índice válido na Constant Pool, que deve ser do tipo "Class". 
 *              Resolve para uma String que contém o nome da Classe.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Super Class</td>
 *          <td>
 *              Aponta para um índice válido na Constante Pool, que deve ser do tipo "Class".
 *              Resolve para uma String que contém o nome da Classa da qual herda.
 *              <br>
 *              Caso o valor da flag "Super Class" seja igual a 0, significa que ela não herda
 *              de nenhuma outra classe. Isso só deve ocorrer para a classe Object.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Interfaces Count</td>
 *          <td>
 *              Campo responsável por determinar o tamanho do vetor de Interfaces. Cada posição
 *              do vetor deve ser um índice válido na Constant Pool do tipo "Class". 
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Fields Count</td>
 *          <td>
 *              Campo responsável por determinar o tamanho do vetor de Fields.
 *              Cada entrada no vetor é implementada pela struct field_info.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Methods Count</td>
 *          <td>
 *              Campo responsável por determinar o tamanho do vetor de Methods.
 *              Cada entrada no vetor é implementada pela struct method_info.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Attributes Count</td>
 *          <td>
 *              Campo responsável por determinar o tamanho do vetor de Attributes.
 *              Cada entrada no vetor é implementada pela struct attribute_info.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Interfaces</td>
 *          <td>
 *              Após armazenar o tamanho no campo interfaces_count, e caso o valor
 *              armazenado seja diferente de "0", será chamado o método setInterfaces(),
 *              que irá armazenar as n-entradas (definidas pelo interfaces_count) na Constant Pool.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Fields</td>
 *          <td>
 *              Após armazenar o tamanho no campo fields_count, e caso o valor armazenado
 *              seja diferente de "0", será chamado o método setFields(), que irá armazenar os n-fields
 *              (definidos pelo fields_count) da Classe.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Methods</td>
 *          <td>
 *              Após armazenar o tamanho no campo methods_count, e caso o valor armazenado
 *              seja diferente de "0", será chamado o método setMethods(), que irá armazenar os n-methods
 *              (definidos pelo methods_count) da Classe.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Attributes</td>
 *          <td>
 *              Após armazenar o tamanho no campo attributes_count, e caso o valor armazenado
 *              seja diferente de "0", será chamado o método setAttribute(attribute_info*), que irá armazenar
 *              os n-attributes (definidos pelo attributes_count) da Classe.
 *          </td>
 *      </tr>
 *  </table>
 * 
 *  Após o armazenamento dos campos descritos acima, toda a informação relacionada a classe que será exibida/executada
 *  está pronta para ser utilizada.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::setInterfaces()
 *  \brief Método responsável por alocar e ler os índices de Interfaces na Constant Pool.
 * 
 *  Caso o campo interfaces_count seja diferente de "0", significa a existência de interfaces na Classe.
 *  O método irá alocar o espaço necessário, com base no valor armazenado em interfaces_count, e um laço
 *  será executado para efetuar a leitura das n-interfaces. Para cada interface lida, o índice do bytecode
 *  avança em 2 bytes.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::setFields()
 *  \brief Método responsável por alocar e ler as informações de cada field associado à Classe.
 * 
 *  Caso o campo fields_count seja diferente de "0", significa a existência de fields no Classe.
 *  O método irá alocar o espaço necessário, com base no valor armazenado em fields_count, e um laço
 *  será executado para efetuar a leitura dos campos da structs field_info.
 *  Há um segundo laço, interno ao primeiro, que avalia o campo sendo lido com auxílio de um switch.
 *  São 4 campos que serão lidos e, para cada um, o índice do bytecode avança 2 bytes.
 *  Ao final da leitura dos 4 campos do n-ésimo Field, caso o campo attributes_count seja diferente de "0",
 *  o método setAttributes(attribute_info*) será chamado para armazenar os n-atributos do Field.
 * 
 *  \return Nada é retornado.
 */

/** \fn void JavaClass::setMethods()
 *  \brief Método responsável por alocar e ler as informações de cada method associado à Classe.
 *  
 *  Caso o campo methods_count seja diferente de "0", significa a existência de methods no Classe.
 *  O método irá alocar o espaço necessário, com base no valor armazenado em methods_count, e um laço
 *  será executado para efetuar a leitura dos campos da struct method_info.
 *  Há um segundo laço, interno ao primeiro, que avalia o campo sendo lido com auxílio de um switch.
 *  São 4 campos que serão lidos e, para cada um, o índice do bytecode avança 2 bytes.
 *  Ao final da leitura dos 4 campos do n-ésimo Method, caso o campo attributes_cout seja diferente de "0",
 *  o método setAttributes(attribute_info*) será chamado para armazenar os n-atributos do Method.
 *  
 *  \return Nada é retornado.
 */

/** \fn u1* JavaClass::setAttribute(attribute_info *attr)
 *  \brief Método responsável por ler e armazenar o atributo da Classe, Field ou Method.
 * 
 *  O método lê o atributo, associado a uma Classe/Field/Method. O método chama o método
 *  verifyAttrType(u2) e armazena o atributo de acordo com o tipo retornado.
 *  A implementação oficial da JVM reconhece um total de 19 tipos de atributos. A implementação aqui apresentada
 *  Reconhece apenas 14 dos 19 atributos, eles são brevemente apresentados a seguir:
 * 
 *  <table>
 *      <tr>
 *          <th>Atributo</th>
 *          <th>Descrição</th>
 *      </tr>
 *      <tr>
 *          <td>Constant Value</td>
 *          <td>
 *              Atributo de tamanho fixo associado a um Field. Representa o valor constante de um Field. Não pode
 *              haver mais de um atributo "Constant Value" para cada Field da classe Java. O atributo é definido pela
 *              struct attribute_info::info::ConstantValue_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Code</td>
 *          <td>
 *              Atributo de tamanho variável associado a um Method. Contém instruções e informações auxiliares para um
 *              único método, método de inicialização de instância, ou inicialização de classe ou instnância. Toda
 *              implementação da JVM deve reconhecer o atributo Code. Se um Method é "Native" ou "Abstract", ele não deve
 *              conter um atributo Code. Caso contrário, um Method deve conter exatamente um atributo Code. O atributo é
 *              implementado pela struct attribute_info::info::Code_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Exception</td>
 *          <td>
 *              Atributo de tamanho variável associado a um Method. Indica quais exceções um Method pode lançar. Deve haver
 *              no máximo um atributo Exception associado a cada Method. É implmentado pela struct attribute_info::info::Exceptions_Attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Inner Class</td>
 *          <td>
 *              Atributo de tamanho variável associado a uma Class. Se a Constant Pool da classe ou interface contém uma entrada do tipo CONSTANT_Class
 *              que representa uma classe ou interface que não é membro de um pacote, então a Class deve conter exatamente um atributo Inner Class.
 *              É implementado pela struct attribute_info::info::InnerClasses_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Enclosing Method</td>
 *          <td>
 *              É um atributo opcional de tamanho fixo associado a uma Class. Uma classe deve conter um atributo Enclosing Method se, e somente se, for
 *              uma classe anônima ou local. Uma classe não pode conter mais do que um atributo desse tipo. É implementado pela struct
 *              attribute_info::info::EnclosingMethod_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Synthetic</td>
 *          <td>
 *              É um atributo de tamanho fixo associado a uma Class, Field ou Method. Um membro de uma classe que não aparece no código-fonte deve estar
 *              marcado por um atributo Synthetic, ou senão deve ter uma flag ACC_Synthetic setada. É implementado pela struct attribute_info. Como o atributo
 *              não contém campos, além dos comuns a todos os atributos, ele não está contido, explicitamente, a union attribute_info::info.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Signature</td>
 *          <td>
 *              É um atributo de tamanho fixo associado a uma Class, Field ou Method. Grava informações de assinatura genéricas para qualquer classe, interface,
 *              construtor ou membro o qual a assinatura genérica na linguagem de programação Java iria incluir referências para variáveis de tipo ou tipos parametrizados.
 *              É implementado pela struct attribute_info::info::Signature_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Source File</td>
 *          <td>
 *              É um atributo opcional de tamanho fixo associado a uma Class. Não pode haver mais do que um atributo Source File para cada Class.
 *              É implementado pela struct attribute_info::info::SourceFile_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Source Debug Extension</td>
 *          <td>
 *              É um atributo opcional de tamanho variável associado a uma Class. Não pode haver mais do que um atributo Source Debug Extension para cada Class.
 *              É implementado pela struct attribute_info::info::SourceDebugExtension_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Line Number Table</td>
 *          <td>
 *              É um atributo opcional de tamanho variável associado à tabela de atributos de um Code. Pode ser utilizado por debbugers para determinar qual parte do
 *              vetor de Code da JVM corresponde a uma dada linha do arquivo fonte original. É implementado pela struct attribute_info::info::LineNumberTable_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Local Variable Table</td>
 *          <td>
 *              É um atributo opcional de tamanho variável associado à tabela de atributos de um Code. Pode ser utilizado por debbugers para determinar o valor de uma
 *              dada variável local durante a execução de um método. Caso apareçam na tabela de atributos do Code, podem aparecer em qualquer ordem. Não podem haver mais de
 *              um Local Variable Table no atributo Code. É implementado pela struct attribute_info::info::LocalVariableTable_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Local Variable Type Table</td>
 *          <td>
 *              É um atributo opcional de tamanho variável associado à tabela de atributos de um Code. Pode ser utilizado por debbugers para determinar o valor de uma
 *              dada variável local durante a execução de um método. Caso apareçam na tabela de atributos do Code, podem aparecer em qualquer ordem. Não podem haver mais de
 *              um Local Variable Type Table no atribute Code. É implementado pela struct attribute_info::info::LocalVariableTypeTable_attribute.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Deprecated</td>
 *          <td>
 *              É um atributo opcional de tamanho fixo associado a uma Class, Field ou Method. Uma classe, interface, método ou campo pode ser marcado usando o atributo Deprecated
 *              para indicar que o mesmo foi substituído. O interpretador ou compilador pode usar essa marcação para avisar ao usuário da substituição da classe, interface, método
 *              ou campo. É implementado pela struct attribute_info. Como o atributo não contém campos, além dos comuns a todos os atributos, ele não está contido, explicitamente,
 *              a union attribute_info::info.
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Bootstrap Methods</td>
 *          <td>
 *              É um atributo de tamanho variável associado a uma Class. Grava especificadores de métodos referenciados por instruções <i>invokedynamic</i>. Deve haver apenas um
 *              Bootstrap Method por classe caso a Constant Pool tenha pelo menos uma entrada do tipo CONSTANT_InvokeDynamic. É implementado pela struct
 *              attribute_info::info::BootstrapMethods_attribute.
 *          </td>
 *      </tr>
 *  </table>
 * 
 *  Para os outros 5 atributos (Stack Map Table, Runtime Visible Annotations, Runtime Invisible Annotations, Runtime Visible Parameter Annotations e Runtime Invisible Parameter Annotations),
 *  essa implementação apenas os ignora em silêncio.
 * 
 *  \param *attr; Ponteiro para o vetor de atributos da Classe, Field ou Method.
 *  \return Retorna um vetor de bytes com a informação do atributo alocado.
 */

/** \fn int JavaClass::verifyAttrType(u2 name_index)
 *  \brief Método responsável por verificar qual tipo de atributo sendo lido.
 * 
 *  O método recebe como argumento uma entrada válida para a Constant Pool, que deve ser do tipo UTF-8 e conter um tipo válido de atributo (para ver os tipos válidos, acesse o método setAttribute()).
 *  Após acessar a Constant Pool, o método chama o método getUtf8 para processar o vetor de caracteres em UTF-8 para gerar uma String. Após esse processamento, utiliza-se um switch para verificar qual 
 *  o tipo do atributo e, então, é retornado um valor numérico entre 1 e 19. Como a função setAttribute() só processa 14 dos 19 atriutos existentes, alguns dos tipos nunca seram retornados. Especificamente os tipos:
 *  3, 14, 15, 16, 17 e 18
 * 
 *  \param name_index; Short sem sinal que busca o tipo de atributo na Constant Pool.
 *  \return Retorna um inteiro contendo o tipo do atributo.
 */

/** \fn std::string JavaClass::getUtf8(u2)
 *  \brief Método responsável por processar vetores de caracteres UTF-8 contidos na Constant Pool.
 *  
 *  O método recebe como argumento uma entrada válida para a Constant Pool e, com essa entrada, acessa a mesma para buscar um vetor de bytes UTF-8. Após essa busca, é verificado o tamanho do vetor,
 *  e um novo vetor, de char, é alocado e setado para conter os caracteres. Depois o método transforma o vetor de char em uma std::string, libera o vetor de char que havia sido alocado e, por fim,
 *  retorna a String.
 * 
 *  \param name_index; Unsigned short contendo um valor válido de acesso à Constant Pool.
 *  \return Retorna uma std::string contendo um nome válido, em UTF-8, da Constant Pool.
 */

/** \mainpage
 *  Grupo 3:<br>
 *  - Bernardo Costa Nascimento 140080279<br>
 *  - Frederico Paiva Lenza 140082221<br>
 *  - Cristiano Cardoso 150058349<br>
 *  - João Pedro Silva Sousa 150038381<br>
 *  - Vitor Moraes Dellamora 160056802<br>
 * 
 * <br><br>
 *  A Java Virtual Machine, aqui documentada, interpreta código Java até, no máximo,
 *  a versão Java7.
 *  Para compilar, rode o seguinte comando:
 *  > g++ --std=c++11 jvm.cpp ClassPrinter.cpp Frame.cpp Heap.cpp JavaClass.cpp Security.cpp Types.cpp
 *  
 *  <br><br>
 *  Após compilar, para executar programas Java (arquivos .class) basta executar o comando:
 *  > jvm.exe <arquivo .class>
 * 
 *  <br><br>
 *  Para acessar a documentação das classes, acesse o link "Classes -> Lista de Componentes"
 *  no menu superior.
 */