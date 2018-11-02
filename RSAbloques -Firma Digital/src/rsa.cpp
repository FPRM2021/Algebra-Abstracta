#include "rsa.h"

RSABloques::RSABloques(int bits)
{
    GenPrime(p, bits);
    GenPrime(q, bits);

    while(p==q){
        GenPrime(p, bits);
        GenPrime(q, bits);
    }
    //Valor de N de 1024 bits
    N = p * q;
    //Se halla Phi
    Phi = (p - ZZ(1)) * (q - ZZ(1));
    //Genera 1 < e < Phi
    RandomBnd(e, Phi);
    while (GCD(e, Phi) != 1 || e == 1)
        RandomBnd(e, Phi);
    //Inversa de e
    d=euclext(e, Phi);
    d=Modulo(d, Phi);
}

//Constructor receptor (Genera claves)
RSABloques::RSABloques(int bits, ZZ eB, ZZ NB)
{
    this->eB=eB;
    this->NB=NB;
    GenPrime(p, bits);
    GenPrime(q, bits);

    while(p==q){
        GenPrime(p, bits);
        GenPrime(q, bits);
    }
    //Valor de N de 1024 bits
    N = p * q;
    //Se halla Phi
    Phi = (p - ZZ(1)) * (q - ZZ(1));
    //Genera 1 < e < Phi
    RandomBnd(e, Phi);
    while (GCD(e, Phi) != 1 || e == 1)
        RandomBnd(e, Phi);
    //Inversa de e
    d=euclext(e, Phi);
    d=Modulo(d, Phi);
}

RSABloques::RSABloques(ZZ e, ZZ p, ZZ q, ZZ eB, ZZ NB){
    this->e=e;
    this->p=p;
    this->q=q;
    this->NB=NB;
    this->eB=eB;
    N = p * q;
    Phi = (p - ZZ(1)) * (q - ZZ(1));
    d=euclext(e, Phi);
    d=Modulo(d, Phi);
}

string RSABloques::toBloques(string msn, int sizN)
{
    string res, digAct;
    string fill = to_string(23);
    int digsizAlf =to_string(23).length();
    int k = sizN - 1;

    //string de numeros posicion
    for (int i = 0; i < msn.length(); i++) {
        digAct = msn[i];
        //Format posicion, then add to res
        res += formatInt(alfabeto.find(digAct), digsizAlf);
    }

    int ite = Modulo(res.length(), k);
    //No hace falta relleno
    if (ite == 0)
        return res;

    //Relleno con sizAlf
    ite = k - ite;
    int i = 0;
    while (i < ite) {
        res += fill[Modulo(i, fill.length())];
        i++;
    }
    return res;
}

string RSABloques::toBloquesN(string msn, int sizN)
{
    string fill = to_string(23);
    int digsizAlf =to_string(23).length();
    int k = sizN - 1;

    int ite = Modulo(msn.length(), k);

    if (ite == 0)
        return msn;

    ite = k - ite;
    int i = 0;
    while (i < ite) {
        msn += fill[Modulo(i, fill.length())];
        i++;
    }
    return msn;
}

string RSABloques::fromBloques(string msn, int sizAlf)
{
    string res, digAct;
    int digsizAlf = to_string(sizAlf).length();
    int pos;

    int ite = msn.length() / digsizAlf;
    for (int i = 0; i < ite; i++) {
        pos = stoi(msn.substr(i * digsizAlf, digsizAlf));
        res += alfabeto[pos];
    }
    return res;
}

string RSABloques::formatInt(int num, int dig)
{
    string res;
    res = to_string(num);
    //5 dig - 1size = 4 ceros a la izq
    int difeSize = dig - res.length();

    while (difeSize > 0) {
        res = '0' + res;
        difeSize--;
    }
    return res;
}

string RSABloques::formatZZ(ZZ num, int dig)
{
    string res;
    res += zzToString(num);
    //5 dig - 1size = 4 ceros a la izq
    int difeSize = dig - res.length();

    while (difeSize > 0) {
        res = '0' + res;
        difeSize--;
    }
    return res;
}

string RSABloques::cifrar(string msn)
{
    dp=Modulo(d,p-1);
    dq=Modulo(d,q-1);
    string res,rub,fd;
    string resTemp,rubtmp,fdtmp;

    int Ndig = zzToString(N).length();
    int k = Ndig - 1;

    int NdigB = zzToString(NB).length();
    int kB = NdigB - 1;

    //Convert msn a numeros para bloque

    ZZ opera;


    //RSA

    resTemp = toBloques(msn, NdigB);
    int nBloques = resTemp.length()/kB;
    for (int i = 0; i < nBloques; i++){
        opera = ZZ(stoi(resTemp.substr(i * kB, kB)));
        opera = expoMB(opera, eB, NB);
        res += formatZZ(opera, NdigB);
    }
    //Rubrica

    rubtmp = toBloquesN(res, Ndig);
    nBloques=rubtmp.length()/ k;
    for (int i = 0; i < nBloques; i++){
        opera = ZZ(stoi(rubtmp.substr(i * k, k)));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P,ZZ(0));
        rub += formatZZ(opera, Ndig);
    }
    //FirmaD

    fdtmp = toBloquesN(rub, NdigB);
    nBloques=fdtmp.length()/ kB;
    for (int i = 0; i < nBloques; i++) {
        opera = ZZ(stoi(fdtmp.substr(i * kB, kB)));
        opera = expoMB(opera, eB, NB);
        fd += formatZZ(opera, NdigB);
    }
    return fd;
    //return res;
}

string RSABloques::descifrar(string msn)
{
    string res;
    string resTemp,fdtmp,rubtmp;

    dp=Modulo(d,p-1);
    dq=Modulo(d,q-1);

    int Ndig = zzToString(N).length();
    int k = Ndig - 1;

    int NdigB = zzToString(NB).length();
    int kB = NdigB - 1;

    ZZ opera;

    //firmadigital
    int nBloques = msn.length()/Ndig;
    for (int i = 0; i < nBloques; i++) {
        opera = ZZ(stoi(msn.substr(i * Ndig, Ndig)));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P,ZZ(0));
        fdtmp += formatZZ(opera, k);
    }
    //rubrica
    nBloques =fdtmp.length()/NdigB;
    for (int i = 0; i < nBloques; i++) {
        opera = ZZ(stoi(fdtmp.substr(i * NdigB, NdigB)));
        opera = expoMB(opera, eB, NB);
        rubtmp += formatZZ(opera, kB);
    }
    //rsa
    nBloques = rubtmp.length()/Ndig;
    for (int i = 0; i < nBloques; i++) {
        opera = ZZ(stoi(rubtmp.substr(i * Ndig, Ndig)));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P,ZZ(0));
        resTemp += formatZZ(opera, k);
    }

    //Convertir a mensaje
    res = fromBloques(resTemp, alfabeto.length());

    return res;
}
