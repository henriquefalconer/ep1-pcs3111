#include <functional>
#include "iofuncs.h"

#include "Pagina.h"
#include "Perfil.h"
#include "PessoaNaoVerificada.h"
#include "PessoaVerificada.h"
#include "Postagem.h"
#include "RedeSocial.h"
#include "Story.h"

using FuncaoDeRede = function<void(RedeSocial*)>;
using CriadorDeFuncaoDeRede = function<FuncaoDeRede(Perfil*)>;

bool imprimirOpcoes(
    RedeSocial* redeSocial,
    string textoInicial,
    string textoFinal,
    int quantidadeDeOpcoes,
    string* opcoes,
    FuncaoDeRede* funcoes,
    bool temOpcaoZero = false
) {
    print(textoInicial);

    for (int i = 1; i <= quantidadeDeOpcoes; i++)
        print(i % (quantidadeDeOpcoes + 1 - temOpcaoZero), ") ", opcoes[i - 1]);

    int escolha = input<int>(textoFinal, '\n');

    if (escolha <= 0 || escolha > quantidadeDeOpcoes - temOpcaoZero)
        return false;

    int posicao = escolha - 1;

    funcoes[posicao](redeSocial);

    return true;
}

void cadastroPessoa(RedeSocial* redeSocial) {
    string nome = input("Informe os dados da pessoa\nNome: ");
    bool verificada = simounao("Verificada (s/n)? ");
    if (!verificada) {
        redeSocial->adicionar(new Perfil(nome));
        print();
        return;
    }
    redeSocial->adicionar(new PessoaVerificada(nome, input("Email: ", '\n')));
}

void criarOpcoesUsuario(
    RedeSocial* redeSocial,
    string* opcoesUsuario,
    FuncaoDeRede* funcoes,
    CriadorDeFuncaoDeRede criarFuncao
) {
    for (int i = 0; i < redeSocial->getQuantidadeDePerfis(); i++) {
        auto perfil = redeSocial->getPerfis()[i];

        opcoesUsuario[i] =
            perfil->getNome() +
            (dynamic_cast<PessoaVerificada*>(perfil) ? " (Verificada)" : "");

        funcoes[i] = criarFuncao(perfil);
    }
}

bool mostrarOpcoesUsuario(
    RedeSocial* redeSocial,
    string textoInicial,
    CriadorDeFuncaoDeRede criarFuncao
) {
    int quantidadeDePerfis = redeSocial->getQuantidadeDePerfis();

    auto opcoesUsuario = new string[quantidadeDePerfis];
    auto funcoes = new FuncaoDeRede[quantidadeDePerfis];

    criarOpcoesUsuario(redeSocial, opcoesUsuario, funcoes, criarFuncao);

    bool opcaoEscolhida = imprimirOpcoes(redeSocial,
        textoInicial,
        "Digite o numero ou 0 para cancelar: ",
        quantidadeDePerfis,
        opcoesUsuario,
        funcoes);

    delete[] opcoesUsuario;
    delete[] funcoes;

    return opcaoEscolhida;
}

void cadastroPagina(RedeSocial* redeSocial) {
    string nome = input("Informe os dados da pagina\nNome: ", '\n');

    auto criarFuncao = [&](Perfil* perfil) -> FuncaoDeRede {
        return [&, perfil](RedeSocial* redeSocial) {
            if (auto pessoaVerificada = dynamic_cast<PessoaVerificada*>(perfil))
                redeSocial->adicionar(new Pagina(nome, pessoaVerificada));

            else
                print("Somente pessoas verificadas podem ser proprietarias\n");
        };
    };

    mostrarOpcoesUsuario(redeSocial, "Proprietario:", criarFuncao);
}

FuncaoDeRede opcoesLogadas(Perfil* perfil) {
    auto fazerPostagem = [perfil](RedeSocial* redeSocial) {
        int dataDeFim;
        bool ehStory = simounao("Story (s/n): ");
        int data = input<int>("Data: ");
        if (ehStory) dataDeFim = input<int>("Data de fim: ");
        string texto = input("Texto: ", '\n');

        perfil->adicionarPostagem(
            ehStory ? new Story(texto, data, dataDeFim, perfil)
                    : new Postagem(texto, data, perfil));
    };

    auto verPostagens = [perfil](RedeSocial* redeSocial) {
        int quantidadeDePostagensDosContatos;
        auto postagens = perfil->getPostagensDosContatos(
            input<int>("Data: "), 
            quantidadeDePostagensDosContatos
        );

        print("Postagens dos ultimos 3 dias:");

        for (int i = 0; i < quantidadeDePostagensDosContatos; i++)
            postagens[i]->imprimir();
        
        delete[] postagens;

        print();
    };

    auto listaDeAdicionarContato = [perfil](RedeSocial* redeSocial) {
        bool foiPossivelAdicionar;

        auto adicionarContato = [&, perfil](Perfil* novoContato) {
            return [=, &foiPossivelAdicionar](RedeSocial* redeSocial) {
                foiPossivelAdicionar = perfil->adicionarContato(novoContato);
            };
        };

        bool opcaoEscolhida =
            mostrarOpcoesUsuario(redeSocial, "Perfil:", adicionarContato);

        if (!opcaoEscolhida || !foiPossivelAdicionar)
            print("Contato nao adicionado");
    };

    return [=](RedeSocial* redeSocial) {
        bool repetir;

        do {
            printinl(perfil->getNome());

            if (auto pessoaVerificada = dynamic_cast<PessoaVerificada*>(perfil))
                printinl(" - ", pessoaVerificada->getEmail());

            else if (auto pagina = dynamic_cast<Pagina*>(perfil))
                printinl(
                    "\nProprietario ", pagina->getProprietario()->getNome());

            print("\nContatos: ", perfil->getQuantidadeDeContatos(), "\n---");

            string opcoes[] = { 
                "Fazer postagem",
                "Ver postagens dos contatos",
                "Adicionar contato",
                "Deslogar" 
            };

            FuncaoDeRede funcoes[] = {
                fazerPostagem, 
                verPostagens, 
                listaDeAdicionarContato 
            };

            repetir = imprimirOpcoes(
                redeSocial,
                "Escolha uma opcao:",
                "",
                4,
                opcoes,
                funcoes,
                true
            );
        } while (repetir);
    };
}

void logar(RedeSocial* redeSocial) {
    mostrarOpcoesUsuario(redeSocial, "Escolha um perfil:", opcoesLogadas);
}

void interfaceGrafica(RedeSocial* redeSocial) {
    string opcoes[] = {
        "Cadastrar Pessoa", 
        "Cadastrar Pagina", 
        "Logar", 
        "Terminar" 
    };

    FuncaoDeRede funcoes[] = { cadastroPessoa, cadastroPagina, logar };

    while (
        imprimirOpcoes(
            redeSocial,
            "Escolha uma opcao",
            "",
            4,
            opcoes,
            funcoes,
            true
        )
    ) {}
}

int main() {
    auto redeSocial = new RedeSocial();

    interfaceGrafica(redeSocial);

    delete redeSocial;

    return 0;
}
