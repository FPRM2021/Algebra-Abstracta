#pragma once

#ifndef FMATH_H
#define FMATH_H
#include <NTL/ZZ.h>
#include <vector>
#include <sstream>
#include <string>

using namespace NTL;
using namespace std;

inline ZZ Modulo(ZZ a,ZZ n){
    ZZ res=a-n*(a/n);
    if(res<0)
        res+=n;
    return res;
}

inline int Modulo(int a,int n){
    int res=a-n*(a/n);
    if(res<0)
        res+=n;
    return res;
}

inline ZZ mcd(ZZ a, ZZ n){
    ZZ b=a;
    ZZ c=n;
    ZZ res= Modulo(b,c);
    while(res!=0){
        b=c;
        c=res;
        res=Modulo(b,c);
    }
    return c;
}

inline ZZ euclext(ZZ a, ZZ b){
    ZZ d,x,y,q,r;
    ZZ x2=ZZ(1);
    ZZ x1=ZZ(0);
    ZZ y2=ZZ(0);
    ZZ y1=ZZ(1);
    if(b==0){
        d=a;
        x=ZZ(1);
        y=ZZ(1);
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

inline ZZ inversoM(ZZ a,ZZ b){
    ZZ c=euclext(a,b);
    while(c<ZZ(0)){
        c+=b;
    }
    return c;
}

inline ZZ expoM(ZZ a,ZZ e,ZZ N){
    ZZ exp=ZZ(1);
    ZZ x=Modulo(a,N);
    while(e>ZZ(0)){
        if(Modulo(e,ZZ(2))==ZZ(1))
            exp=Modulo(exp*x,N);
        x=Modulo(x*x,N);
        e=e/ZZ(2);
    }
    return exp;
}

inline ZZ expoMB(ZZ a,ZZ e,ZZ N){
    int k=NumBits(e);
    ZZ c;
    if(bit(e,k-1)==1)
        c=a;
    else
        c=ZZ(1);
    for(int i=k-2;i>=0;i--){
        c=Modulo(c*c,N);
        if(bit(e,i)==1)
            c=Modulo(c*a,N);
    }
    return c;
}

inline ZZ expoMBS(ZZ a,vector<int> e,ZZ N, int k){
    ZZ c;
    if(e[k-1]==1)
        c=a;
    else
        c=ZZ(1);
    for(int i=k-2;i>=0;i--){
        c=Modulo(c*c,N);
        if(e[i]==1)
            c=Modulo(c*a,N);
    }
    return c;
}

inline ZZ resch(vector<ZZ> a, vector<ZZ> p, ZZ k){
    ZZ tam=to_ZZ(a.size());
    for(int i=0;i<tam;i++){
        a[i]=Modulo(a[i],p[i]);
    }

    ZZ P=to_ZZ(1);
    vector<ZZ> Pi;
    vector<ZZ> qi;
    for(int i=0;i<tam;i++){
        if(p[i]<1)
            return to_ZZ(0);
        for(int j=0;j<tam;j++){
                if(mcd(p[i],p[j])!=1 && i!=j)
                    return to_ZZ(0);
        }
        P*=p[i];
    }

    ZZ x0=to_ZZ(0);

    for(int i=0;i<tam;i++){
        Pi.push_back(P/p[i]);
        qi.push_back(Modulo(euclext(Pi[i],p[i]),p[i]));
        x0+=Modulo(a[i]*Pi[i]*qi[i],P);
    }
    x0=Modulo(x0,P);
    return x0+P*k;
}

inline string zzToString(const ZZ x)
{
    stringstream buffer;
    buffer << x;
    return buffer.str();
}

#endif
