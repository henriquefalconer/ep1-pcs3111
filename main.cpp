#include <iostream>

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
    int escolha;

    cout << textoInicial << endl;
    for (int i = 1; i <= quantidadeDeOpcoes; i++)
        cout << i % (quantidadeDeOpcoes + 1 - temOpcaoZero) << ") "
             << opcoes[i - 1] << endl;

    cout << textoFinal;
    cin >> escolha;
    cout << endl;

    if (escolha <= 0 || escolha > quantidadeDeOpcoes - temOpcaoZero)
        return false;

    int posicao = escolha - 1;

    funcoes[posicao](redeSocial);

    return true;
}

void imprimirOpcoesERepetir(
    RedeSocial* redeSocial,
    string textoInicial,
    string textoFinal,
    int quantidadeDeOpcoes,
    string* opcoes,
    FuncaoDeRede* funcoes,
    bool temOpcaoZero = false
) {
    while (imprimirOpcoes(redeSocial, 
        textoInicial,
        textoFinal,
        quantidadeDeOpcoes,
        opcoes,
        funcoes,
        temOpcaoZero)) {
    }
}

bool simOuNao(string texto) {
    string escolha;
    cout << texto;
    cin >> escolha;
    return escolha == "s" || escolha.empty();
}

void cadastroPessoa(RedeSocial* redeSocial) {
    string nome;
    cout << "Informe os dados da pessoa" << endl << "Nome: ";
    cin >> nome;
    bool verificada = simOuNao("Verificada (s/n)? ");
    if (!verificada) {
        redeSocial->adicionar(new Perfil(nome));
        cout << endl;
        return;
    }
    string email;
    cout << "Email: ";
    cin >> email;
    redeSocial->adicionar(new PessoaVerificada(nome, email));
    cout << endl;
}

void criarOpcoesUsuario(RedeSocial* redeSocial,
    string** opcoesUsuario,
    FuncaoDeRede** funcoes,
    CriadorDeFuncaoDeRede criarFuncao) {
    int quantidadeDePerfis = redeSocial->getQuantidadeDePerfis();
    int quantidadeDePerfilNaoExcluidos = quantidadeDePerfis;

    *opcoesUsuario = new string[quantidadeDePerfilNaoExcluidos];
    *funcoes = new FuncaoDeRede[quantidadeDePerfilNaoExcluidos];

    for (int i = 0; i < quantidadeDePerfis; i++) {
        Perfil* perfil = redeSocial->getPerfis()[i];

        if (dynamic_cast<PessoaVerificada*>(perfil))
            (*opcoesUsuario)[i] = perfil->getNome() + " (Verificada)";
        else
            (*opcoesUsuario)[i] = perfil->getNome();

        (*funcoes)[i] = criarFuncao(perfil);
    }
}

bool mostrarOpcoesUsuario(
    RedeSocial* redeSocial,
    string textoInicial,
    CriadorDeFuncaoDeRede criarFuncao
) {
    string* opcoesUsuario;
    FuncaoDeRede* funcoes;

    criarOpcoesUsuario(redeSocial, &opcoesUsuario, &funcoes, criarFuncao);

    bool opcaoEscolhida = imprimirOpcoes(redeSocial,
        textoInicial,
        "Digite o numero ou 0 para cancelar: ",
        redeSocial->getQuantidadeDePerfis(),
        opcoesUsuario,
        funcoes);

    delete[] opcoesUsuario;
    delete[] funcoes;

    return opcaoEscolhida;
}

void cadastroPagina(RedeSocial* redeSocial) {
    string nome;
    cout << "Informe os dados da pagina" << endl << "Nome: ";
    cin >> nome;

    auto criarFuncao = [&nome](Perfil* perfil) -> FuncaoDeRede {
        if (PessoaVerificada* pessoaVerificada =
                dynamic_cast<PessoaVerificada*>(perfil))
            return [&nome, pessoaVerificada](RedeSocial* redeSocial) {
                redeSocial->adicionar(new Pagina(nome, pessoaVerificada));
            };

        return [](RedeSocial* redeSocial) {
            cout << "Somente pessoas verificadas podem ser proprietarias"
                 << endl
                 << endl;
        };
    };

    mostrarOpcoesUsuario(redeSocial, "Proprietario:", criarFuncao);
}

FuncaoDeRede opcoesLogadas(Perfil* perfil) {
    auto fazerPostagem = [perfil](RedeSocial* redeSocial) {
        bool ehStory = simOuNao("Story (s/n): ");
        int data, dataDeFim;
        string texto;
        cout << "Data: ";
        cin >> data;

        if (ehStory) {
            cout << "Data de fim: ";
            cin >> dataDeFim;
        }

        cout << "Texto: ";
        cin >> texto;

        if (ehStory)
            perfil->adicionarPostagem(
                new Story(texto, data, dataDeFim, perfil));
        else
            perfil->adicionarPostagem(new Postagem(texto, data, perfil));

        cout << endl;
    };

    auto verPostagens = [perfil](RedeSocial* redeSocial) {
        int data, quantidadeDePostagensDosContatos;
        cout << "Data: ";
        cin >> data;
        Postagem** postagens = perfil->getPostagensDosContatos(
            data, quantidadeDePostagensDosContatos);

        cout << "Postagens dos ultimos 3 dias:" << endl;

        for (int i = 0; i < quantidadeDePostagensDosContatos; i++)
            postagens[i]->imprimir();

        cout << endl;
    };

    auto listaDeAdicionarContato = [perfil](RedeSocial* redeSocial) {
        bool foiPossivelAdicionar;

        auto adicionarContato = [perfil, &foiPossivelAdicionar](
                                    Perfil* novoContato) -> FuncaoDeRede {
            return [perfil, novoContato, &foiPossivelAdicionar](
                       RedeSocial* redeSocial) {
                foiPossivelAdicionar = perfil->adicionarContato(novoContato);
            };
        };

        bool opcaoEscolhida =
            mostrarOpcoesUsuario(redeSocial, "Perfil:", adicionarContato);

        if (!opcaoEscolhida || !foiPossivelAdicionar)
            cout << "Contato nao adicionado" << endl << endl;
    };

    return [perfil, fazerPostagem, verPostagens, listaDeAdicionarContato](
               RedeSocial* redeSocial) {
        bool repetir;

        do {
            cout << perfil->getNome();

            if (PessoaVerificada* pessoaVerificada =
                    dynamic_cast<PessoaVerificada*>(perfil))
                cout << " - " << pessoaVerificada->getEmail();

            else if (Pagina* pagina = dynamic_cast<Pagina*>(perfil))
                cout << endl
                     << "Proprietario " << pagina->getProprietario()->getNome();

            cout << endl << "Contatos: " << perfil->getQuantidadeDeContatos();

            cout << endl << "---" << endl;

            repetir = imprimirOpcoes(redeSocial,
                "Escolha uma opcao:",
                "",
                4,
                (string[]){ "Fazer postagem",
                    "Ver postagens dos contatos",
                    "Adicionar contato",
                    "Deslogar" },
                (FuncaoDeRede[]){ fazerPostagem,
                    verPostagens,
                    listaDeAdicionarContato,
                    cadastroPessoa },
                true);
        } while (repetir);
    };
}

void logar(RedeSocial* redeSocial) {
    mostrarOpcoesUsuario(redeSocial, "Escolha um perfil:", opcoesLogadas);
}

void interfaceGrafica(RedeSocial* redeSocial) {
    imprimirOpcoesERepetir(redeSocial,
        "Escolha uma opcao",
        "",
        4,
        (string[]){
            "Cadastrar Pessoa", "Cadastrar Pagina", "Logar", "Terminar" },
        (FuncaoDeRede[]){
            cadastroPessoa, cadastroPagina, logar, cadastroPessoa },
        true);
}

int main() {
    RedeSocial* redeSocial = new RedeSocial();

    interfaceGrafica(redeSocial);

    delete redeSocial;

    return 0;
}