#include "fogadas.h"
double szorzo(int darab)
{
    double sv_szorzo;

    if (darab > 0)
        sv_szorzo = (1 + (5 / (pow(2, darab - 1))));
    else
        sv_szorzo = 0;

    return sv_szorzo;
}
