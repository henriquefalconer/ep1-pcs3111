#include "PessoaVerificada.h"

#include <iostream>

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
    cout << getEmail() << endl;
    Perfil::imprimir();
}
