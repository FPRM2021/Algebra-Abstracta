#ifndef FIRMAD_H
#define FIRMAD_H
#include "mathfunc.h"
#include <vector>

class firmad
{
    public:
        firmad(ZZ,ZZ,ZZ,ZZ);
        void printv(vector<ZZ>);
        ZZ crearRub(ZZ);
        ZZ crearFD();
        ZZ descifrarFD(ZZ);
        ZZ descifrarRub();
    private:
        ZZ rub,ds,da,Na,eb,Nb;
};

#endif // FIRMAD_H
