#include "enigma.h"

enigma::enigma(int a,int b,int c,string clave){
    this->a=a;
    this->b=b;
    this->c=c;
    this->clave=clave;
    srotor(rtr1,a,l1);
    srotor(rtr2,b,l2);
    srotor(rtr3,c,l3);
}

int enigma::modulo(int a){
    int n=alfabeto.size();
    int r=a-(a/n*n);
    if(r<0)
        r+=n;
    return r;
}

void enigma::srotor(string &rtr,int cr,int &l){
    switch(cr){
    case 1:
        rtr=rotor1;
        l=17;
        break;
    case 2:
        rtr=rotor2;
        l=5;
        break;
    case 3:
        rtr=rotor3;
        l=22;
        break;
    case 4:
        rtr=rotor4;
        l=10;
        break;
    case 5:
        rtr=rotor5;
        l=26;
        break;
    }
}

string enigma::cifrado(string msn)
{
    string cypher;
    string tmp=clave;
    int p;
    int r1=alfabeto.find(clave[0]);
    int r2=alfabeto.find(clave[1]);
    int r3=alfabeto.find(clave[2]);

    for(int i=0;i<msn.size();i++){

        r3=modulo(r3+1);

        if(r3==l3)
            r2=modulo(r2+1);

        if(r2==l2)
            r1=modulo(r1+1);

        if(r1==l1){
            r2=0;
            r3=0;
        }

        tmp=rtr3[modulo(r3+alfabeto.find(msn[i]))];
        tmp=rtr2[modulo(r2+alfabeto.find(tmp)-r3)];
        tmp=rtr1[modulo(r1+alfabeto.find(tmp)-r2)];

        tmp=reflec[modulo(alfabeto.find(tmp)-r1)];

        p=modulo(rtr1.find(alfabeto[modulo(alfabeto.find(tmp)+r1)])-r1);
        p=modulo(rtr2.find(alfabeto[modulo(p+r2)])-r2);
        tmp=alfabeto[modulo(rtr3.find(alfabeto[modulo(p+r3)])-r3)];

        cypher+=tmp;
    }
    for(int i=0;i<cypher.size();i++)
        cout<<cypher[i];
        cout<<endl;
    return cypher;
}

string enigma::descifrado(string msn)
{
    string decypher;
    string tmp=clave;
    int p;
    int r1=alfabeto.find(clave[0]);
    int r2=alfabeto.find(clave[1]);
    int r3=alfabeto.find(clave[2]);

    for(int i=0;i<msn.size();i++){

        r3=modulo(r3+1);

        if(r3==l3)
            r2=modulo(r2+1);

        if(r2==l2)
            r1=modulo(r1+1);

        if(r1==l1){
            r2=0;
            r3=0;
        }

        tmp=rtr3[modulo(r3+alfabeto.find(msn[i]))];
        tmp=rtr2[modulo(r2+alfabeto.find(tmp)-r3)];
        tmp=rtr1[modulo(r1+alfabeto.find(tmp)-r2)];

        tmp=reflec[modulo(alfabeto.find(tmp)-r1)];

        p=modulo(rtr1.find(alfabeto[modulo(alfabeto.find(tmp)+r1)])-r1);
        p=modulo(rtr2.find(alfabeto[modulo(p+r2)])-r2);
        tmp=alfabeto[modulo(rtr3.find(alfabeto[modulo(p+r3)])-r3)];

        decypher+=tmp;
    }
    for(int i=0;i<decypher.size();i++)
        cout<<decypher[i];
        cout<<endl;
    return decypher;
}

