#include "rsa.h"
#include <NTL/ZZ.h>
#include <iostream>
#include <string>
#include <vector>
#include "mathfunc.h"
#include <sstream>

using namespace std;
using namespace NTL;

int main()
{
    // Claves de receptor
    RSABloques receptor(8);
    RSABloques emisor(ZZ(22451),ZZ(179),ZZ(137),/*ZZ(161),ZZ(34933)*/receptor.e,receptor.N);
    //RSABloques emisor(8,ZZ(161),ZZ(34933));

    //Claves para claveCustom
    //    RSABloques emisor(ZZ(7313), ZZ(35621));
    //    RSABloques emisor(ZZ(193), ZZ(35909));
    //    RSA prob(ZZ(34855), ZZ(813473));

    receptor.eB=emisor.e;
    receptor.NB=emisor.N;

    string cifrado, descifrado;
    string msn = "THEREISASTRANGERINTOWN";

    cifrado = emisor.cifrar(msn);
    cout << cifrado <<endl;

    descifrado = receptor.descifrar(cifrado);
    cout << descifrado <<endl;
}
