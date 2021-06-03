#include "Postagem.h"
#include "iofuncs.h"

Postagem::Postagem(string texto, int data, Perfil* autor)
    : texto(texto), data(data), autor(autor) {}

Postagem::~Postagem() { print("Destrutor de postagem: ", texto); }

// Getters
string Postagem::getTexto() { return this->texto; }

int Postagem::getData() { return this->data; }

Perfil* Postagem::getAutor() { return this->autor; }

// Methods
void Postagem::imprimir() {
    print("Texto: ", getTexto(), " - Data: ", getData(), " - Autor: ", getAutor()->getNome());
}
