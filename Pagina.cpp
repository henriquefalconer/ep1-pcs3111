#include "Pagina.h"

#include <iostream>

Pagina::Pagina(string nome, PessoaVerificada* proprietario)
    : Perfil(nome), proprietario(proprietario) {
    adicionarContato(proprietario);
}

Pagina::~Pagina() {}

// Getters
PessoaVerificada* Pagina::getProprietario() { return proprietario; }

// Methods
void Pagina::imprimir() {
    cout << "Nome: " << getNome()
         << " - Proprietario: " << proprietario->getNome() << endl;
}
