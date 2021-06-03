#include "Postagem.h"

#include <iostream>

Postagem::Postagem(string texto, int data, Perfil* autor)
    : texto(texto), data(data), autor(autor) {}

Postagem::~Postagem() { cout << "Destrutor de postagem: " << texto << endl; }

// Getters
string Postagem::getTexto() { return this->texto; }

int Postagem::getData() { return this->data; }

Perfil* Postagem::getAutor() { return this->autor; }

// Methods
void Postagem::imprimir() {
    cout << "Texto: " << getTexto() << " - Data: " << getData()
         << " - Autor: " << getAutor()->getNome() << endl;
}
