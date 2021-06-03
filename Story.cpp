#include "Story.h"

#include <iostream>

Story::Story(string texto, int data, int dataDeFim, Perfil* autor)
    : Postagem(texto, data, autor), dataDeFim(dataDeFim) {}

Story::~Story() {}

// Getters
int Story::getDataDeFim() { return this->dataDeFim; }

// Methods
void Story::imprimir() {
    cout << "Texto: " << getTexto() << " - Data: " << getData()
         << " - Data De Fim: " << getDataDeFim()
         << " - Autor: " << getAutor()->getNome() << endl;
}
