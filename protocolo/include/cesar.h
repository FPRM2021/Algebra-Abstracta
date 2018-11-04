#ifndef CESAR_H
#define CESAR_H
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class cesar
{
    public:
        string alfabeto={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        cesar(int);
        cesar();
        string cifrado(string);
        string descifrado(string);
        AlgExtEu(int, int);
        modulo(int, int);
        inversoM(int,int);
        mcd(int, int);
        int l=alfabeto.size();
        int getclave();
    private:
        int clave;
};

#endif // CESAR_H
