#include "firmad.h"

firmad::firmad(ZZ da,ZZ Na,ZZ eb,ZZ Nb)
{
    this->da=da;
    this->Na=Na;
    this->eb=eb;
    this->Nb=Nb;
}

void firmad::printv(vector<ZZ> v){
    for(int i=0;i<v.size();i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

ZZ firmad::crearRub(ZZ m)
{
    rub=(expoM(m,da,Na));
    return rub;
}

ZZ firmad::crearFD()
{
    ds=(expoM(rub,eb,Nb));
    return ds;
}

ZZ firmad::descifrarFD(ZZ m)
{

}

ZZ firmad::descifrarRub()
{

}
