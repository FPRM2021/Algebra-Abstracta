#include "enigma.h"
int enigma::AlgExtEu(int a, int b){
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

int enigma::modulo(int a, int b){
    if(a==0)
        return 0;
    int res=a-(a/b*b);
    if(res<0)
        res+=b;
    return res;
}

int enigma::inversoM(int a,int b){
    int c=AlgExtEu(a,b);
    while(c<0){
        c+=b;
    }
    return c;
}

int enigma::mcd(int a, int b){
        int r=1;
    while(r!=0){
        r=modulo(a,b);
        a=b;
        b=r;
    }

    return a;
}

enigma::enigma(int a1,int b1,int c1,string cl,string stecks){
    a=a1;
    b=b1;
    c=c1;
    clave=cl;
    srotor(rtr1,a,l1);
    srotor(rtr2,b,l2);
    srotor(rtr3,c,l3);
    stecker=stecks;
}

enigma::enigma(int a1,int b1,int c1,string cl,string ls,string stecks){
    a=a1;
    b=b1;
    c=c1;
    clave=cl;
    srotor(rtr1,a,l1);
    srotor(rtr2,b,l2);
    srotor(rtr3,c,l3);
    l1=alfabeto.find(ls[0]);
    l2=alfabeto.find(ls[1]);
    l3=alfabeto.find(ls[2]);
    stecker=stecks;
}

void enigma::srotor(string &rtr,int cr,int &l){
    switch(cr){
    case 1:
        rtr=rotor1;
        l=alfabeto.find('R');
        break;
    case 2:
        rtr=rotor2;
        l=alfabeto.find('F');
        break;
    case 3:
        rtr=rotor3;
        l=alfabeto.find('W');
        break;
    case 4:
        rtr=rotor4;
        l=alfabeto.find('K');
        break;
    case 5:
        rtr=rotor5;
        l=alfabeto.find('A');
        break;
    case 6:
        rtr=rotor6;
        l=alfabeto.find('A');
        break;
    case 7:
        rtr=rotor7;
        l=alfabeto.find('A');
        break;
    case 8:
        rtr=rotor8;
        l=alfabeto.find('N');
        break;
    }
}

void enigma::steckers(){
    int a=alfabeto.find(stecker[0]);
    int b=alfabeto.find(stecker[1]);
    alfabeto[a]=stecker[1];
    alfabeto[b]=stecker[0];
}

string enigma::cifrado(string msn)
{
    string cypher;

    int r1=alfabeto.find(clave[0]);
    int r2=alfabeto.find(clave[1]);
    int r3=alfabeto.find(clave[2]);

    for(int i=0;i<msn.size();i++){

        if(msn[i]==stecker[0])
            msn[i]=stecker[1];

        else if(msn[i]==stecker[1])
            msn[i]=stecker[0];

        string tmp;
        int p;

        r3=modulo(r3+1,l);

        if(alfabeto[r3]==alfabeto[modulo(l3,l)])
            r2=modulo(r2+1,l);

        /*if(alfabeto[r2]==alfabeto[modulo(l2-1,l)]){
            r2=modulo(r2+1,l);
        }*/

        if(alfabeto[r3]==alfabeto[modulo(l3,l)] && alfabeto[r2]==alfabeto[modulo(l2,l)])
            r1=modulo(r1+1,l);

        tmp=rtr3[modulo(r3+alfabeto.find(msn[i]),l)];
        tmp=rtr2[modulo(r2+alfabeto.find(tmp)-r3,l)];
        tmp=rtr1[modulo(r1+alfabeto.find(tmp)-r2,l)];

        tmp=reflec[modulo(alfabeto.find(tmp)-r1,l)];

        p=modulo(rtr1.find(alfabeto[modulo(alfabeto.find(tmp)+r1,l)])-r1,l);
        p=modulo(rtr2.find(alfabeto[modulo(p+r2,l)])-r2,l);
        tmp=alfabeto[modulo(rtr3.find(alfabeto[modulo(p+r3,l)])-r3,l)];

        if(tmp[0]==stecker[0])
            tmp=stecker[1];
        else if(tmp[0]==stecker[1])
            tmp=stecker[0];

        cypher+=tmp;

    }

    return cypher;
}

string enigma::descifrado(string msn)
{
    return cifrado(msn);
}

