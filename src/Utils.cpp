#include "../include/Utils.h"

#include <unistd.h> // NULL

///////////////////////////////
/// METODOS DA CLASSE TIMER ///
///////////////////////////////

Timer::Timer()
{
    iniciaContagem();
}

void Timer::iniciaContagem()
{
    gettimeofday(&tstart, NULL);
}

float Timer::finalizaContagem()
{
    gettimeofday(&tnow, NULL);

    if (tstart.tv_usec > tnow.tv_usec) {
        tnow.tv_usec += 1000000;
        tnow.tv_sec--;
    }

    return (float)(tnow.tv_sec - tstart.tv_sec) +
           ((float)tnow.tv_usec - (float)tstart.tv_usec)/1000000.0;
}
