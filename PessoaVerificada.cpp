#include "PessoaVerificada.h"
#include "iofuncs.h"

PessoaVerificada::PessoaVerificada(string nome, string email)
    : Perfil(nome), email(email) {}

PessoaVerificada::PessoaVerificada(string nome)
    : PessoaVerificada(nome, "email.padrao@usp.br") {}

PessoaVerificada::~PessoaVerificada() {
    // TODO: adicionar lógica de liberação de memória
}

// Getters
string PessoaVerificada::getEmail() { return this->email; }

// Methods
void PessoaVerificada::imprimir() {
    print(getEmail());
    Perfil::imprimir();
}
