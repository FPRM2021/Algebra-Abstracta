#ifndef RSA_H
#define RSA_H
#include "mathfunc.h"

class RSABloques {
public:
    const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ZZ Phi,d, dp, dq, ap, aq, p, q;
    vector<int> Be,Bdp,Bdq;
    string toBloques(string msn, int sizN);
    string toNumbers(string msn);
    string fromBloques(string msn, int sizAlf);
    string formatInt(int num, int dig);
    string formatZZ(ZZ num, int dig);
    string cifrsa(string);
    string descifrsa(string);
    string cifrub(string);
    string descifrub(string);
    string ciffirm(string);
    string desciffirm(string);

public:
    ZZ e, N,eB,NB;
    int Ndig,k,NdigB,kB;
    string cifrar(string msn);
    string descifrar(string cipher);
    RSABloques(int);
    RSABloques(ZZ e, ZZ p, ZZ q);
};

#endif // RSABLOQUES_H
