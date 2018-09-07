#ifndef ENIGMA_H
#define ENIGMA_H
#include <string>
#include <iostream>

using namespace std;

class enigma
{
    public:
        enigma(int,int,int,string);
        string alfabeto={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        string cifrado(string);
        string descifrado(string);
        int modulo(int);
        void srotor(string&,int,int&);
    private:
        int a,b,c,l1,l2,l3;
        string rtr1,rtr2,rtr3;
        string rotor1={"EKMFLGDQVZNTOWYHXUSPAIBRCJ"};
        string rotor2={"AJDKSIRUXBLHWTMCQGZNPYFVOE"};
        string rotor3={"BDFHJLCPRTXVZNYEIWGAKMUSQO"};
        string rotor4={"ESOVPZJAYQUIRHXLNFTGKDCMWB"};
        string rotor5={"VZBRGITYUPSDNHLXAWMJQOFECK"};
        string reflec={"YRUHQSLDPXNGOKMIEBFZCWVJAT"};
        string clave;
};

#endif // ENIGMA_H
