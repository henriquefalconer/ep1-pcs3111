#include "Perfil.h"
#include "iofuncs.h"

Perfil::Perfil(string nome)
    : nome(nome),
      contatos(new Perfil*[MAXIMO_CONTATOS]),
      postagens(new Postagem*[MAXIMO_POSTAGENS]) {}

Perfil::~Perfil() {
    print("Destrutor de perfil: ", nome, " - Quantidade de postagens feitas: ", quantidadeDePostagens);

    delete[] contatos;

    for (int i = 0; i < quantidadeDePostagens; i++)
        delete postagens[i];

    delete[] postagens;

    print("Perfil deletado");
}

// Getters
string Perfil::getNome() { return nome; }

int Perfil::getQuantidadeDeContatos() { return quantidadeDeContatos; }

int Perfil::getQuantidadeDePostagens() { return quantidadeDePostagens; }

Perfil** Perfil::getContatos() { return contatos; }

Postagem** Perfil::getPostagens() { return postagens; }

Postagem** Perfil::getPostagensDosContatos(int data, int& quantidade) {
    auto postagensDosContatos = new Postagem*[quantidadeDeContatos * MAXIMO_POSTAGENS];

    quantidade = 0;

    for (int i = 0; i < quantidadeDeContatos; i++) {
        for (int j = 0; j < contatos[i]->getQuantidadeDePostagens(); j++) {
            auto postagem = contatos[i]->getPostagens()[j];

            if (data >= postagem->getData() && data - postagem->getData() <= 3)
                postagensDosContatos[quantidade++] = postagem;
        }
    }

    return postagensDosContatos;
}

// Methods
bool Perfil::adicionarContato(Perfil* perfil) {
    if (quantidadeDeContatos == MAXIMO_CONTATOS) return false;

    for (int i = 0; i < quantidadeDeContatos; i++)
        if (contatos[i] == perfil) return false;

    contatos[quantidadeDeContatos++] = perfil;

    perfil->adicionarContato(this);

    return true;
}

bool Perfil::adicionarPostagem(Postagem* p) {
    if (quantidadeDePostagens == MAXIMO_POSTAGENS) return false;
    postagens[quantidadeDePostagens++] = p;
    return true;
}

void Perfil::imprimir() {
    print("\nNome: ", nome, "\nNumero de postagens feitas: ", quantidadeDePostagens);
    for (int i = 0; i < quantidadeDePostagens; i++)
        print("Postagens na data: ", postagens[i]->getData(), " - Texto: ", postagens[i]->getTexto());
    if (quantidadeDeContatos == 0)
        print("Sem contatos ");
    else {
        for (int i = 0; i < quantidadeDeContatos; i++) {
            for (int j = 0; j < contatos[i]->getQuantidadeDePostagens(); j++)
                print(
                    "Postagens na data ", 
                    contatos[i]->getPostagens()[j]->getData(), 
                    " do contato ", 
                    contatos[i]->getNome(), 
                    " - Texto: ", 
                    contatos[i]->getPostagens()[j]->getTexto()
                );
        }
    }
}
