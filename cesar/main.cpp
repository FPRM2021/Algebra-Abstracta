#include "cesar.h"

int main()
{
    string mensaje;
    int clave;
    cout<<"Introduce la clave: ";
    cin>>clave;
    cout<<"Introduce el mensaje: ";
    cin>>mensaje;
    cesar Emisor(clave);
    string mc=Emisor.cifrado(mensaje);
    cout<<mc<<endl;
    cesar Receptor(clave);
    string msn=Receptor.descifrado(mc);
    cout<<msn;
    return 0;
}
