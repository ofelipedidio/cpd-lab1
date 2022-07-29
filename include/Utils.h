#ifndef UTILS_H
#define UTILS_H

#include <sys/time.h>

typedef struct
{
    long long int trocas;
    long long int comparacoes;
} Estatisticas;

class Timer{
    public:
        Timer();

        void iniciaContagem();
        float finalizaContagem();

    private:
        struct timeval tstart, tnow;
};

#endif // UTILS_H
