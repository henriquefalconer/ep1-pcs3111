#ifndef PERFIL_H
#define PERFIL_H

#include <string>
using namespace std;

#include "Postagem.h"
class Postagem;

#define MAXIMO_CONTATOS 20
#define MAXIMO_POSTAGENS 20

class Perfil {
   private:
    string nome;
    Perfil** contatos;
    int quantidadeDeContatos = 0;
    Postagem** postagens;
    int quantidadeDePostagens = 0;

   public:
    Perfil(string nome);
    virtual ~Perfil();
    // Getters
    string getNome();
    virtual int getQuantidadeDeContatos();
    virtual int getQuantidadeDePostagens();
    virtual Perfil** getContatos();
    virtual Postagem** getPostagens();
    virtual Postagem** getPostagensDosContatos(int data, int& quantidade);
    // Methods
    virtual bool adicionarContato(Perfil* perfil);
    virtual bool adicionarPostagem(Postagem* p);
    virtual void imprimir();
};

#endif  // PERFIL_H
