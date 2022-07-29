#include "../include/Dados.h"

#include <iostream>     // std::cout
#include <algorithm>    // std::sort


//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

Dados::Dados() {
    //construtor

    // Inicializa gerador de numeros aleatorios (da biblioteca random)
    std::random_device r;
    gerador = new std::default_random_engine(r());

}

Dados::~Dados() {
    // destrutor

    delete (gerador);
}

void swap(std::vector<Registro> *vec, int i, int j, Registro *temp, Estatisticas *est) {
    est->trocas++;
    *temp = (*vec)[i];
    (*vec)[i] = (*vec)[j];
    (*vec)[j] = *temp;
}

////////////////////////////
/// METODOS DE ORDENACAO ///
////////////////////////////

Estatisticas Dados::ordenaComBubbleSort() {
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    unsigned int tamanho = this->registros.size();
    unsigned int m = tamanho-1;
    int k = 0;
    bool troca;
    Registro temp;
    do {
        troca = false;
        for (int i = 0; i < m; i++) { //varreduras do vetor
            est.comparacoes++;
            if (this->registros[i] > this->registros[i + 1]) {  //em caso de troca
                swap(&this->registros, i, i+1, &temp, &est);
                k = i;
                troca = true;
            }
        }
        m = k;
    } while (troca);

    return est;
}

Estatisticas Dados::ordenaComInsertionSort() {
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    int tamanho = this->registros.size();
    Registro chave;
    int j, i;
    for (j = 0; j < tamanho; j++) { //varreduras do vetor
        chave = this->registros[j];
        i = j - 1;
        while ((i >= 0)) {  //em caso de troca
            est.comparacoes++;
            if ((this->registros[i] > chave)) {
                est.trocas++;
                this->registros[i + 1] = this->registros[i];
                i = i - 1;
            } else {
                break;
            }
        }

        est.trocas++;
        this->registros[i + 1] = chave;
    }


    return est;
}

Estatisticas Dados::ordenaComShellSort(TipoShellSort tipo) {
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(this->registros.size(), tipo);

    int tamanho = this->registros.size();
    int gapSize = sequenciaDeGaps.size() - 1;
    Registro chave;
    int valorGap, posGap, gaps, j;

    for (; gapSize >= 0; gapSize--) { //percorre vetor de Gaps
        valorGap = sequenciaDeGaps[gapSize];
        for (gaps = 0; gaps <= valorGap; gaps++) { //percorre os Gaps do sort
            for (posGap = gaps; posGap < tamanho; posGap = posGap + valorGap) {   //percorre a sequ�ncia de um Gap
                est.trocas++;
                chave = this->registros[posGap];
                j = posGap - valorGap;
                while ((j >= gaps) && (this->registros[j] > chave)) { //troca elementos
                    est.comparacoes++;
                    est.trocas++;
                    this->registros[j + valorGap] = this->registros[j];
                    j = j - valorGap;
                }
                est.comparacoes++;
                est.trocas++;
                this->registros[j + valorGap] = chave;
            }
        }
    }

    return est;
}


bool Dados::checaSeOrdenacaoFoiEstavel() {
    for (unsigned int i = 0; i < registros.size() - 1; i++)
        if (registros[i].getChave() == registros[i + 1].getChave() &&
            registros[i].getDadoSatelite() > registros[i + 1].getDadoSatelite())
            return false;

    return true;
}

bool Dados::checaSeRegistrosOrdenados() {
    for (unsigned int i = 0; i < registros.size() - 1; i++)
        if (registros[i] > registros[i + 1])
            return false;

    return true;
}

//////////////////////////
/// METODOS AUXILIARES ///
//////////////////////////

std::vector<int> Dados::geraSequenciaDeGaps(int tamanho, TipoShellSort tipo) {
    std::vector<int> v;

    int e = 1;
    v.push_back(e);

    if (tipo == SHELL59) {         // (Shell,1959) - sequencia 1, 2, 4, 8, 16, 32, ...
        while (e < tamanho) {
            e *= 2;
            v.push_back(e);
        }

    } else if (tipo == KNUTH71) {   // (Knuth,1971) - sequencia 1, 4, 13, 40, 121, 364, ...
        while (e < tamanho) {
            e = e * 3 + 1;
            v.push_back(e);
        }

    } else if (tipo == TOKUDA92) {  // (Tokuda,1992) - sequencia 1, 4, 9, 20, 46, 103, ...
        int i = 1;
        while ((e = ceil((9.0 * pow(9.0, i) / pow(4.0, i) - 4.0) / 5.0)) < tamanho) {
            v.push_back(e);
            i++;
        }
    } else if (tipo ==
               CIURA01) {  // (Ciura,2001) - sequencia 1, 4, 10, 23, 57, 132, 301, 701 - daqui em diante nao tem prova de otimalidade
        int seq[8] = {1, 4, 10, 23, 57, 132, 301, 701};

        int i = 1;
        while (i < 8 && seq[i] < tamanho) {
            v.push_back(seq[i]);
            i++;
        }

        int e = 701;
        while ((e = floor(2.25 * (float) e)) < tamanho)
            v.push_back(e);
    }

    return v;
}

void Dados::inicializaRegistrosComVetor(const std::vector<int> &vetor_auxiliar) {
    // Reseta vetor de registros
    registros.clear();

    // Reserva novo tamanho do vetor de registros
    unsigned int tamanho = vetor_auxiliar.size();
    registros.reserve(tamanho);

    // Copia valores para vetor de registros
    for (unsigned int i = 0; i < tamanho; i++) {
        int c = vetor_auxiliar[i];
        int s = i + 1;

        registros.push_back(Registro(c, s));
    }
}

void Dados::geraVetorAleatorio(unsigned int tamanho, int minimo_possivel, int maximo_possivel) {
    // Seta distribuicao de chaves como valor aleatorio uniforme entre 'minimo_possivel' e 'maximo_possivel'
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);

    // Cria vetor auxiliar e preenche com valores aleatorios
    std::vector<int> vetor_auxiliar(tamanho);
    for (unsigned int i = 0; i < tamanho; i++) {
        vetor_auxiliar[i] = chave_aleatoria(*gerador);
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel) {
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for (unsigned int i = 0; i < tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort(vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorQuaseOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel) {
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for (unsigned int i = 0; i < tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort(vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Da uma leve embaralhada, dentro de uma distancia 'range'
    int range = tamanho / 50;
    if (range < 5)
        range = 5;
    std::uniform_int_distribution<int> gap_para_troca(0, range);

    for (unsigned int i = 0; i < tamanho; i++) {
        int k = gap_para_troca(*gerador);
        if (k % 5 == 0 && i + k < tamanho) {
            int temp = vetor_auxiliar[i + k];
            vetor_auxiliar[i + k] = vetor_auxiliar[i];
            vetor_auxiliar[i] = temp;
        }
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorReverso(unsigned int tamanho, int minimo_possivel, int maximo_possivel) {
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for (unsigned int i = 0; i < tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort(vetor_auxiliar.begin(), vetor_auxiliar.end(), std::greater<int>());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::imprime_registros() {
    for (unsigned int i = 0; i < registros.size(); i++) {
        std::cout << registros[i] << ' ';
    }
    std::cout << std::endl;
}

