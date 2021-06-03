#include <iostream>
#include <string>
using namespace std;

// Imprime na saída padrão todos os argumentos passados.
inline void printinl() {}

// Imprime na saída padrão todos os argumentos passados.
template <typename T, typename... Args>
inline void printinl(T t, Args... args) {
    cout << t;
    printinl(args...);
}

// Imprime na saída padrão todos os argumentos passados, adicionando uma quebra de linha no fim da sequência.
// Obs.: Caso você não queira que seja impressa a quebra de linha, utilize a função printinl.
template <typename... Args>
inline void print(Args... args) {
    printinl(args..., '\n');
}

// Lê a string digitada na entrada padrão, imprimindo opcionalmente um texto antes e depois do que foi digitado.
// Obs.: Para retornar uma variável cujo tipo que não é string, utilizar o argumento de template: int i = input<int>();
template <typename T = string, typename U = string, typename V = string>
inline T input(U antes = "", V depois = "") {
    T t;
    printinl(antes);
    cin >> t;
    printinl(depois);
    return t;
}

// Lê a string digitada na entrada padrão, retornando true se for igual a "s" ou "", e false caso contrário.
// Opcionalmente, também imprime um texto antes e depois do que foi digitado.
template <typename U = string, typename V = string>
inline bool simounao(U antes = "", V depois = "") {
    string escolha = input(antes, depois);
    return escolha == "s" || escolha.empty();
}
