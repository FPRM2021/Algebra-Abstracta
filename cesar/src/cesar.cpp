#include "cesar.h"

cesar::cesar(int c)
{
    clave=c;
}

string cesar::cifrado(string msn){
    string cypher;
    int tmp;
    for(int i=0;i<msn.size();i++){
        tmp=modulo((alfabeto.find(msn[i])+clave),alfabeto.size());
        cypher+=alfabeto[tmp];
    }
    return cypher;
}

string cesar::descifrado(string msn){
    string descypher;
    int tmp;
    for(int i=0;i<msn.size();i++){
        tmp=modulo((alfabeto.find(msn[i])-clave),alfabeto.size());
        descypher+=alfabeto[tmp];
    }
    return descypher;
}

int cesar::modulo(int a, int n){
    int r=a-(a/n*n);
    if(r<0)
        r+=n;
    return r;
}
