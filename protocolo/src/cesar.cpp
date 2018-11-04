#include "cesar.h"

int cesar::AlgExtEu(int a, int b){
    /*if(a>b){
        a=a^b;
        b=a^b;
        a=a^b;
    }*/
    int d,x,y,q,r;
    int x2=1;
    int x1=0;
    int y2=0;
    int y1=1;
    if(b==0){
        d=a;
        x=1;
        y=1;
    }
    while(b>0){
        q=a/b;
        r=a-q*b;
        x=x2-q*x1;
        y=y2-q*y1;
        a=b;
        b=r;
        x2=x1;
        x1=x;
        y2=y1;
        y1=y;
    }
    d=a;
    x=x2;
    y=y2;
    return x;
}

int cesar::modulo(int a, int b){
    if(a==0)
        return 0;
    int res=a-(a/b*b);
    if(res<0)
        res+=b;
    return res;
}

int cesar::inversoM(int a,int b){
    int c=AlgExtEu(a,b);
    while(c<0){
        c+=b;
    }
    return c;
}

int cesar::mcd(int a, int b){
        int r=1;
    while(r!=0){
        r=modulo(a,b);
        a=b;
        b=r;
    }

    return a;
}

cesar::cesar(int c)
{
    clave=c;
}

cesar::cesar()
{
    srand(time(NULL));
    clave=modulo(rand(),l);
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

int cesar::getclave(){
    return clave;
}
