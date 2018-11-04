#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include <iostream>
#include <afin.h>
#include <cesar.h>
#include <enigma.h>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

class protocolo
{
    public:
        protocolo();
        void cifrado();
        void descifrado();
        string leer(char[]);
        void escribir(char[], string);
        string toString(int);
    private:
};

#endif // PROTOCOLO_H
