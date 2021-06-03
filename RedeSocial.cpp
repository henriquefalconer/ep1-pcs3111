#include "RedeSocial.h"
#include "iofuncs.h"

#include "Pagina.h"
#include "Perfil.h"
#include "PessoaNaoVerificada.h"
#include "PessoaVerificada.h"
#include "Postagem.h"

RedeSocial::RedeSocial(): quantidadeDePerfis(0) {
    perfis = new Perfil*[capacidade];
}

RedeSocial::~RedeSocial() {
    print("Destrutor de RedeSocial: ", quantidadeDePerfis, " perfis ");

    for (int i = 0; i < this->quantidadeDePerfis; i++) delete this->perfis[i];
    delete[] this->perfis;

    print("RedeSocial deletada ");
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
    print("PessoaVerificada: ", quantidadePessoasVerificadas);
    print("PessoaNaoVerificada: ", quantidadePessoasNaoVerificadas);
    print("Pagina: ", quantidadePaginas);
    print("Perfil: ", quantidadePerfis);
}

void RedeSocial::imprimir() {
    print("==================================");
    print("Rede Social: ", quantidadeDePerfis, " perfis");
    print("==================================");
    if (quantidadeDePerfis == 0) {
        print("Sem perfis");
        print("==================================");
    } else {
        for (int i = 0; i < quantidadeDePerfis; i++) {
            perfis[i]->imprimir();
            print("==================================");
        }
    }
    print();
}
