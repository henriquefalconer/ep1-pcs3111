#ifndef REDESOCIAL_H
#define REDESOCIAL_H

#include "Perfil.h"
class Perfil;

class RedeSocial {
   private:
    Perfil** perfis;
    const int capacidade = 100;
    int quantidadeDePerfis = 0;

   public:
    RedeSocial();
    virtual ~RedeSocial();
    // Getters
    Perfil** getPerfis();
    const int getCapacidade();
    int getQuantidadeDePerfis();
    // Methods
    bool adicionar(Perfil* perfil);
    void imprimirEstatisticas();
    void imprimir();
};

#endif  // REDESOCIAL_H
