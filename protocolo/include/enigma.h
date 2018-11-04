#ifndef ENIGMA_H
#define ENIGMA_H
#include <string>
#include <iostream>


using namespace std;

class enigma
{
    public:
        enigma(int,int,int,string,string);
        enigma(int,int,int,string,string,string);
        string alfabeto={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        string cifrado(string);
        string descifrado(string);
        void srotor(string&,int,int&);
        AlgExtEu(int, int);
        modulo(int, int);
        inversoM(int,int);
        mcd(int, int);
        void steckers();
    private:
        int a,b,c,l1,l2,l3;
        string rtr1,rtr2,rtr3;
        string rotor1={"EKMFLGDQVZNTOWYHXUSPAIBRCJ"};
        string rotor2={"AJDKSIRUXBLHWTMCQGZNPYFVOE"};
        string rotor3={"BDFHJLCPRTXVZNYEIWGAKMUSQO"};
        string rotor4={"ESOVPZJAYQUIRHXLNFTGKDCMWB"};
        string rotor5={"VZBRGITYUPSDNHLXAWMJQOFECK"};
        string rotor6={"JPGVOUMFYQBENHZRDKASXLICTW"};
        string rotor7={"NZJHGRCXMYSWBOUFAIVLPEKQDT"};
        string rotor8={"FKQHTLXOCBJSPDZRAMEWNIUYGV"};
        string reflec={"YRUHQSLDPXNGOKMIEBFZCWVJAT"};
        string clave;
        string stecker;
        int l=alfabeto.size();
};

#endif // ENIGMA_H
