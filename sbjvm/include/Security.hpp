#pragma once

#include <iostream>
#include "Constants.hpp"
#include "Structs.hpp"

class Security {
    public:
        static Security* getInstance();
        ~Security();
        Security(const Security&) = delete;
        Security& operator=(const Security&) = delete;

        /*
         * Funções de verificação estão definidas abaixo. Existem três
         * categorias de verificação: estrutural, de ambiente e de conteúdo.
         * Só será realizada a verificação estrutural.
         */
        bool verifyMagic(u4) const;                             // Verifica o 0xCAFEBABE
        bool verifyVersion(u2) const;                           // Verifica se a versão (minor/major) é válida
        bool verifyClassVersion(u2, u2) const;                  // Verifica a compatibilidade do .class
        bool verifyConstantPoolSize(u2) const;                  // Verifica o tamanho da Constant Pool
        bool verifyConstantPoolIndex(u2, u2) const;             // Verifica validade de um índice na Constant Pool
        bool verifyConstantPoolTag(u1);                         // Verifica as TAG's da Constant Pool
        bool verifyValidName(u2) const;                         // Verifica se o nome (field, method, class...) é válido
        bool verifyCodeCPArguments(u1, u2, cp_info*) const;     // Verifica se o argumento é uma referência correta à Constant Pool
        bool verifySymbolicReference(u2, int, cp_info*) const;  // Verifica a referência simbólica
        bool verifySuperClass(u2, cp_info*);                    // Verifica a validade da flag "Super Class"

    private:
        Security();
        static Security* verifier;
};