#ifndef AFIN_H
#define AFIN_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class afin
{
    public:
        afin();
        afin(int, int);
        int modulo(int, int);
        int mcd(int, int);
        int AlgExtEu(int, int);
        int inversoM(int, int);
        string cifrado(string);
        string descifrado(string);
        int geta();
        int getb();
    private:
        string alfabeto="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int a,b,a1;
        int l=alfabeto.size();
        string msn;
};

#endif // AFIN_H
