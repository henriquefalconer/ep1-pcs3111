#include "Perfil.h"
#include "iofuncs.h"

Perfil::Perfil(string nome)
    : nome(nome),
      contatos(new Perfil*[MAXIMO_CONTATOS]),
      postagens(new Postagem*[MAXIMO_POSTAGENS]) {}

Perfil::~Perfil() {
    print("Destrutor de perfil: ", nome, " - Quantidade de postagens feitas: ", quantidadeDePostagens);

    delete[] this->contatos;

    for (int i = 0; i < this->quantidadeDePostagens; i++)
        delete this->postagens[i];

    delete[] this->postagens;

    print("Perfil deletado");
}

// Getters
string Perfil::getNome() { return this->nome; }

int Perfil::getQuantidadeDeContatos() { return this->quantidadeDeContatos; }

int Perfil::getQuantidadeDePostagens() { return this->quantidadeDePostagens; }

Perfil** Perfil::getContatos() { return this->contatos; }

Postagem** Perfil::getPostagens() { return this->postagens; }

Postagem** Perfil::getPostagensDosContatos(int data, int& quantidade) {
    Postagem** postagensDosContatos =
        new Postagem*[this->quantidadeDeContatos * MAXIMO_POSTAGENS];

    quantidade = 0;

    for (int i = 0; i < quantidadeDeContatos; i++) {
        for (int j = 0; j < contatos[i]->getQuantidadeDePostagens(); j++) {
            Postagem* postagem = contatos[i]->getPostagens()[j];

            if (data >= postagem->getData() && data - postagem->getData() <= 3)
                postagensDosContatos[quantidade++] = postagem;
        }
    }

    return postagensDosContatos;
}

// Methods
bool Perfil::adicionarContato(Perfil* perfil) {
    if (this->quantidadeDeContatos == MAXIMO_CONTATOS) return false;

    for (int i = 0; i < this->quantidadeDeContatos; i++)
        if (this->contatos[i] == perfil) return false;

    this->contatos[this->quantidadeDeContatos++] = perfil;

    perfil->adicionarContato(this);

    return true;
}

bool Perfil::adicionarPostagem(Postagem* p) {
    if (this->quantidadeDePostagens == MAXIMO_POSTAGENS) return false;
    this->postagens[this->quantidadeDePostagens++] = p;
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
