#ifndef DADOS_H
#define DADOS_H

#include <vector>
#include <random>

#include "../include/Registro.h"
#include "../include/Utils.h"

enum TipoShellSort { SHELL59, KNUTH71, TOKUDA92, CIURA01};

class Dados
{
    public: // elementos que podem ser acessados externamente

        Dados(); // construtor
        ~Dados(); // destrutor

        // funcoes de ordenacao (a serem completadas)
        Estatisticas ordenaComInsertionSort();
        Estatisticas ordenaComBubbleSort();
        Estatisticas ordenaComShellSort(TipoShellSort tipo);

        // funcoes que geram vetor de registros com valores aleatorios, em ordem, etc
        // caso os parametros 'minimo_possivel' e 'maximo_possivel' nao sejam informados receberão os valores padrao 0 e 1000
        void geraVetorAleatorio(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);
        void geraVetorOrdenado(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);
        void geraVetorQuaseOrdenado(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);
        void geraVetorReverso(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);

        // funcao que imprime vetor de registros
        void imprime_registros();

        // funcao que retorna True se vetor estiver ordenado, senao False
        bool checaSeRegistrosOrdenados();

        // funcao que retorna True se ordenacao estavel aconteceu, senao False
        bool checaSeOrdenacaoFoiEstavel();

    private: // elementos que somente podem ser acessados dentro da classe

        // vetor de registros
        std::vector<Registro> registros;

        // gerador de numeros aleatorios
        std::default_random_engine* gerador;

        // funcao que recebe um vetor por referencia (constante, pois nao será alterado) e inicializa vetor de registros
        void inicializaRegistrosComVetor(const std::vector<int>& vetor_auxiliar);

        // funcao que gera sequencia de gaps
        std::vector<int> geraSequenciaDeGaps(int tamanho, TipoShellSort tipo);

};

#endif // DADOS_H
