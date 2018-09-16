#include "afin.h"

int main()
{
    string mensaje;
    getline(cin,mensaje);
    afin emisor (235,142);
    cout<<emisor.cifrado(mensaje)<<endl;
    cout<<emisor.descifrado("TAXMBQDDA")<<endl;
    cout<<emisor.geta()<<" "<<emisor.getb();
    return 0;
}
