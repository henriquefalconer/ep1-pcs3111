#ifndef PAGINA_H
#define PAGINA_H

#include <string>
using namespace std;

#include "Perfil.h"

#include "PessoaVerificada.h"
class PessoaVerificada;

class Pagina: public Perfil {
   private:
    PessoaVerificada* proprietario;

   public:
    Pagina(string nome, PessoaVerificada* proprietario);
    virtual ~Pagina();
    // Getters
    PessoaVerificada* getProprietario();
    // Methods
    void imprimir();
};

#endif  // PAGINA_H
