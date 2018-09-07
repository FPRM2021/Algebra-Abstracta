#ifndef CESAR_H
#define CESAR_H
#include <string>
#include <iostream>
using namespace std;

class cesar
{
    public:
        string alfabeto={"abcdefghijklmnopqrstuvwxyz"};
        cesar(int);
        string cifrado(string);
        string descifrado(string);
        int modulo(int, int);
    private:
        int clave;

};

#endif // CESAR_H
