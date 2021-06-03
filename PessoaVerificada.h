#ifndef PESSOAVERIFICADA_H
#define PESSOAVERIFICADA_H

#include <string>
using namespace std;

#include "Perfil.h"

class PessoaVerificada: public Perfil {
   private:
    string email;

   public:
    PessoaVerificada(string nome);
    PessoaVerificada(string nome, string email);
    virtual ~PessoaVerificada();
    // Getters
    string getEmail();
    // Methods
    void imprimir();
};

#endif  // PESSOAVERIFICADA_H
