#include <iostream>

#include "include/Dados.h"

// Parametros de entrada do tamanho de coleta dos dados
#define MIN_SIZE 1000
#define MAX_SIZE 10000000
#define INCREASE size *= 2

// Macros que definem a execucao
#define RUN_ALL_CASES LABEL FOR_ALL_ALGORITHMS(RUN_RANDOM) FOR_ALL_ALGORITHMS(RUN_SORTED) FOR_ALL_ALGORITHMS(RUN_ALMOST_SORTED) FOR_ALL_ALGORITHMS(RUN_REVERSED)

#define FOR_ALL_ALGORITHMS(X) \
X("SHELL_SHELL59", est = dados.ordenaComShellSort(SHELL59);) \
X("SHELL_KNUTH71", est = dados.ordenaComShellSort(KNUTH71);) \
X("SHELL_TOKUDA92", est = dados.ordenaComShellSort(TOKUDA92);) \
X("SHELL_CIURA01", est = dados.ordenaComShellSort(CIURA01);) \
X("BUBBLE", est = dados.ordenaComBubbleSort();) \
X("INSERTION", est = dados.ordenaComInsertionSort();) \

#define RUN_RANDOM(name, X) std::cout << "RANDOM_" << name << "\t"; LOOPED(dados.geraVetorAleatorio(size, 1, size); TIMED(X))
#define RUN_SORTED(name, X) std::cout << "SORTED_" << name << "\t"; LOOPED(dados.geraVetorOrdenado(size, 1, size); if(!dados.checaSeRegistrosOrdenados()) {std::cout << "ERROR\n"; return -1;} TIMED(X))
#define RUN_ALMOST_SORTED(name, X) std::cout << "ALMOST_SORTED_" << name << "\t"; LOOPED(dados.geraVetorQuaseOrdenado(size, 1, size); TIMED(X))
#define RUN_REVERSED(name, X) std::cout << "REVERSED_" << name << "\t"; LOOPED(dados.geraVetorReverso(size, 1, size); TIMED(X))

#define TIMED(X) timer.iniciaContagem(); X tempo = timer.finalizaContagem(); std::cout << tempo << "\t" << est.trocas << "\t" << est.comparacoes << "\t" << (dados.checaSeOrdenacaoFoiEstavel() ? "true" : "false") << "\t" << (dados.checaSeRegistrosOrdenados() ? "true" : "false") << "\t"; std::cout.flush();
#define LOOPED(X) for (int size = MIN_SIZE; size <= MAX_SIZE; INCREASE) { X } std::cout << std::endl;

#define LABEL std::cout << "name\t"; LOOPED(std::cout << size << "\ttrocas - " << size << "\tcomparacoes - " << size << "\testavel - " << size << "\tordenado - " << size << "\t";)


int main() {
    Dados dados;
    Timer timer;
    Estatisticas est;
    float tempo;

    RUN_ALL_CASES

    return 0;
}
