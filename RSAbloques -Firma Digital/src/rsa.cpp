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

    dp=Modulo(d,p-1);
    dq=Modulo(d,q-1);
}

RSABloques::RSABloques(ZZ e, ZZ p, ZZ q){
    this->e=e;
    this->p=p;
    this->q=q;
    N = p * q;
    Phi = (p - ZZ(1)) * (q - ZZ(1));
    d=euclext(e, Phi);
    d=Modulo(d, Phi);
    dp=Modulo(d,p-1);
    dq=Modulo(d,q-1);
}

string RSABloques::formatInt(int num, int dig)
{
    string res;
    res = to_string(num);
    int difeSize = dig - res.length();

    while (difeSize > 0) {
        res = '0' + res;
        difeSize--;
    }
    return res;
}

string RSABloques::toNumbers(string msn)
{
    string res, digAct;
    int digsizAlf =to_string(alfabeto.size()).length();
    for (int i = 0; i < msn.length(); i++) {
        digAct = msn[i];
        res += formatInt(alfabeto.find(digAct), digsizAlf);
    }
    return res;
}

string RSABloques::toBloques(string msn, int sizN)
{
    string fill = to_string(22);
    int k = sizN - 1;
    int ite = Modulo(msn.length(), k);
    //No hace falta relleno
    if (ite == 0)
        return msn;

    //Relleno con sizAlf
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

string RSABloques::formatZZ(ZZ num, int dig){
    string res;
    res += zzToString(num);
    int difeSize = dig - res.length();

    while (difeSize > 0) {
        res = '0' + res;
        difeSize--;
    }
    return res;
}

string RSABloques::cifrsa(string msn){
    string resTemp= toBloques(msn, NdigB);
    string res;
    ZZ opera;
    int nBloques =resTemp.length()/kB;
    for (int i = 0; i < nBloques; i++){
        opera = Stringtozz(resTemp.substr(i * kB, kB));
        opera = expoMB(opera, eB, NB);
        res += formatZZ(opera, NdigB);
    }
    return res;
}

string RSABloques::cifrub(string msn){
    string rubtmp = toBloques(msn, Ndig);
    string res;
    ZZ opera;
    int nBloques=rubtmp.length()/ k;
    for (int i = 0; i < nBloques; i++){
        opera = Stringtozz(rubtmp.substr(i * k, k));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P);
        res += formatZZ(opera, Ndig);
    }
    return res;
}

string RSABloques::ciffirm(string msn){
    string fdtmp= toBloques(msn, NdigB);
    string res;
    ZZ opera;
    int nBloques=fdtmp.length()/ kB;
    for (int i = 0; i < nBloques; i++) {
        opera = Stringtozz(fdtmp.substr(i * kB, kB));
        opera = expoMB(opera, eB, NB);
        res += formatZZ(opera, NdigB);
    }
    return res;
}

string RSABloques::desciffirm(string msn){
    string res;
    ZZ opera;
    int nBloques = msn.length()/Ndig;
    for (int i = 0; i < nBloques; i++) {
        opera = Stringtozz(msn.substr(i * Ndig, Ndig));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P);
        res += formatZZ(opera, k);
    }
    return res;
}

string RSABloques::descifrub(string msn){
    string res;
    ZZ opera;
    int nBloques =msn.length()/NdigB;
    for (int i = 0; i < nBloques; i++) {
        opera = Stringtozz(msn.substr(i * NdigB, NdigB));
        opera = expoMB(opera, eB, NB);
        res += formatZZ(opera, kB);
    }
    return res;
}

string RSABloques::descifrsa(string msn){
    string res;
    ZZ opera;
    int nBloques = msn.length()/Ndig;
    for (int i = 0; i < nBloques; i++) {
        opera = Stringtozz(msn.substr(i * Ndig, Ndig));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P);
        res += formatZZ(opera, k);
    }
    return res;
}

string RSABloques::cifrar(string msn)
{
    msn= toNumbers(msn);

    string res,rub,fd;
    string resTemp,rubtmp,fdtmp;


    Ndig = zzToString(N).length();
    k = Ndig - 1;

    NdigB = zzToString(NB).length();
    kB = NdigB - 1;

    //RSA
    res=cifrsa(msn);

    //Rubrica

    rub=cifrub(res);

    //FirmaD
    fd=ciffirm(rub);
    /*
    fdtmp = toBloquesN(rub, NdigB);
    nBloques=fdtmp.length()/ kB;
    for (int i = 0; i < nBloques; i++) {
        opera = Stringtozz(fdtmp.substr(i * kB, kB));
        opera = expoMB(opera, eB, NB);
        fd += formatZZ(opera, NdigB);
    }*/
    //return fd;
    return fd;
}

string RSABloques::descifrar(string msn)
{
    string res;
    string resTemp,fdtmp,rubtmp;



    Ndig = zzToString(N).length();
    k = Ndig - 1;

    NdigB = zzToString(NB).length();
    kB = NdigB - 1;

    //firmadigital
    fdtmp=desciffirm(msn);
    /*ZZ nBloques = ZZ(msn.length()/Ndig);
    for (ZZ i = ZZ(0); i < nBloques; i++) {
        opera = Stringtozz(msn.substr(i * Ndig, Ndig));
        ap=expoMB(opera,dp,p);
        aq=expoMB(opera,dq,q);
        vector<ZZ>a={ap,aq};
        vector<ZZ>P={p,q};
        opera= resch(a,P);
        fdtmp += formatZZ(opera, k);
    }*/
    //rubrica
    rubtmp=descifrub(fdtmp);

    //rsa
    resTemp=descifrsa(rubtmp);

    //Convertir a mensaje
    res = fromBloques(resTemp, alfabeto.length());

    return res;
}
