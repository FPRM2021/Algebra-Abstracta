#ifndef AFIN_H
#define AFIN_H
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class afin
{
    public:
        afin();
        afin(int, int);
        string cifrado(string);
        string descifrado(string);
        int geta();
        int getb();
        AlgExtEu(int, int);
        modulo(int, int);
        inversoM(int,int);
        mcd(int, int);
        string alfabeto="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private:
        int a,b,a1;
        int l=alfabeto.size();
        string msn;
};

#endif // AFIN_H
