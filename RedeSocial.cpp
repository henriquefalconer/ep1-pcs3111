#include "RedeSocial.h"

#include <iostream>

#include "Pagina.h"
#include "Perfil.h"
#include "PessoaNaoVerificada.h"
#include "PessoaVerificada.h"
#include "Postagem.h"

RedeSocial::RedeSocial(): quantidadeDePerfis(0) {
    perfis = new Perfil*[capacidade];
}

RedeSocial::~RedeSocial() {
    cout << "Destrutor de RedeSocial: " << this->quantidadeDePerfis
         << " perfis " << endl;

    for (int i = 0; i < this->quantidadeDePerfis; i++) delete this->perfis[i];
    delete[] this->perfis;

    cout << "RedeSocial deletada " << endl;
}

// Getters
Perfil** RedeSocial::getPerfis() { return this->perfis; }

const int RedeSocial::getCapacidade() { return this->capacidade; }

int RedeSocial::getQuantidadeDePerfis() { return this->quantidadeDePerfis; }

// Methods
bool RedeSocial::adicionar(Perfil* perfil) {
    if (this->quantidadeDePerfis == this->capacidade) return false;
    this->perfis[this->quantidadeDePerfis++] = perfil;
    return true;
}

void RedeSocial::imprimirEstatisticas() {
    int quantidadePessoasVerificadas = 0;
    int quantidadePessoasNaoVerificadas = 0;
    int quantidadePaginas = 0;
    int quantidadePerfis = 0;
    for (int i = 0; i < quantidadeDePerfis; i++) {
        if (dynamic_cast<PessoaVerificada*>(perfis[i]))
            quantidadePessoasVerificadas++;

        else if (dynamic_cast<PessoaNaoVerificada*>(perfis[i]))
            quantidadePessoasNaoVerificadas++;

        else if (dynamic_cast<Pagina*>(perfis[i]))
            quantidadePaginas++;

        else
            quantidadePerfis++;
    }
    cout << "PessoaVerificada: " << quantidadePessoasVerificadas << endl;
    cout << "PessoaNaoVerificada: " << quantidadePessoasNaoVerificadas << endl;
    cout << "Pagina: " << quantidadePaginas << endl;
    cout << "Perfil: " << quantidadePerfis << endl;
}

void RedeSocial::imprimir() {
    cout << "==================================" << endl;
    cout << "Rede Social: " << quantidadeDePerfis << " perfis" << endl;
    cout << "==================================" << endl;
    if (quantidadeDePerfis == 0) {
        cout << "Sem perfis" << endl;
        cout << "==================================" << endl;
    } else {
        for (int i = 0; i < quantidadeDePerfis; i++) {
            perfis[i]->imprimir();
            cout << "==================================" << endl;
        }
    }
    cout << endl;
}
