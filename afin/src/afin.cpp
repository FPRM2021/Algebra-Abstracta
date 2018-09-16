#include "afin.h"

afin::afin()
{
    srand(time(NULL));
    a=modulo(rand(),l);
    b=modulo(rand(),l);
    while(mcd(a,l)!=1){
        a=modulo(rand(),l);
    }
    a1=inversoM(a,l);
}
afin::afin(int m, int n){
    a=m;
    b=n;
        if(mcd(a,l)!=1)
            return;
        else
            a1=inversoM(a,l);
}
int afin::modulo(int a, int b){
    if(a==0)
        return 0;
    int res=a-(a/b*b);
    if(res<0)
        res+=b;
    return res;
}

int afin::AlgExtEu(int a, int b){
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

int afin::mcd(int a, int b){
        int r=1;
    while(r!=0){
        r=modulo(a,b);
        a=b;
        b=r;
    }

    return a;
}
int afin::inversoM(int a,int b){
    int c=AlgExtEu(a,b);
    while(c<0){
        c+=b;
    }
    return c;
}
string afin::cifrado(string mensaje){
        msn=mensaje;
        string cypher;
        string tmp2;
        for(int i=0;i<msn.size();i++){
            int tmp=alfabeto.find(msn[i]);
            tmp=modulo(tmp*a+b,l);
            tmp2=alfabeto[tmp];
            cypher+=tmp2;
        }
        return cypher;
}

string afin::descifrado(string cf){
        string decypher;
        string tmp2;
        for(int i=0;i<cf.size();i++){
            int tmp=alfabeto.find(cf[i]);
            tmp=modulo((tmp-b)*a1,l);
            tmp2=alfabeto[tmp];
            decypher+=tmp2;
        }
        return decypher;
}

int afin::geta(){
    return a;
}
int afin::getb(){
    return b;
}
