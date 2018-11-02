#ifndef RSA_H
#define RSA_H
#include "mathfunc.h"
#include <NTL/ZZ.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using namespace NTL;

class RSABloques {
public:
    const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ZZ Phi,d, dp, dq, ap, aq, p, q;
    vector<int> Be,Bdp,Bdq;
    string toBloques(string msn, int sizN);
    string toBloquesN(string msn, int sizN);
    string fromBloques(string msn, int sizAlf);
    string formatInt(int num, int dig);
    string formatZZ(ZZ num, int dig);

public:
    ZZ e, N,eB,NB;
    string cifrar(string msn);
    string descifrar(string cipher);
    RSABloques(int,ZZ,ZZ);
    RSABloques(int);
    RSABloques(ZZ e, ZZ p, ZZ q, ZZ eB, ZZ NB);
};

#endif // RSABLOQUES_H
