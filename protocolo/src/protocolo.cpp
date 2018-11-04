#include "protocolo.h"

protocolo::protocolo()
{
}



string protocolo::toString(int x){
    string result;
    if(x<10)
        result+='0'+ to_string(x);
    else
        result+=to_string(x);
    return result;
}

string protocolo::leer(char nombre[]){
    ifstream archivo;
    string mensaje;
    archivo.open(nombre,ios::in);
    if(archivo.fail()){
        cout<< "no se pudo abrir el archivo";
        exit(1);
    }
    while(!archivo.eof()){
        getline(archivo,mensaje);
    }
    archivo.close();
    return mensaje;
}

void protocolo::escribir(char nombre[], string mensaje){
    ofstream archivo;
    archivo.open(nombre,ios::out);
    if(archivo.fail()){
        cout<< "no se pudo abrir el archivo";
        exit(1);
    }
    archivo<<mensaje;
    archivo.close();
}

void protocolo::cifrado(){
    string cypher;
    string cypher1;
    string cypherf;
    string msn=leer("mensaje.txt");
    int r1=msn[0]-'0';
    int r2=msn[1]-'0';
    int r3=msn[2]-'0';
    string ir;
    string lr;
    string st;

    for(int i=3;i<msn.size();i++)
        cypher+=msn[i];

    cesar c1;

    cypher=c1.cifrado(cypher);

    for(int i=0;i<3;i++)
        ir+=cypher[i];

    for(int i=3;i<6;i++)
        lr+=cypher[i];

    for(int i=6;i<8;i++)
        st+=cypher[i];

    for(int i=8;i<cypher.size();i++)
        cypher1+=cypher[i];

    enigma e1(r1,r2,r3,ir,lr,st);

    cypher1=e1.cifrado(cypher1);

    afin a1;

    cypher1=a1.cifrado(cypher1);

    cypherf+=toString(a1.geta());
    cypherf+=toString(a1.getb());

    for(int i=0;i<3;i++)
        cypherf+=msn[i];

    for(int i=0;i<3;i++)
        cypherf+=ir[i];

    for(int i=0;i<3;i++)
        cypherf+=lr[i];

    for(int i=0;i<2;i++)
        cypherf+=st[i];

    cypherf+=toString(c1.getclave());

    for(int i=0;i<cypher1.size();i++)
        cypherf+=cypher1[i];

    escribir("cifrado.txt",cypherf);
}

void protocolo::descifrado(){
    string decypher;
    string ir;
    string lr;
    string st;

    string msn=leer("cifrado.txt");

    int a=(msn[0]-'0')*10+msn[1]-'0';
    int b=(msn[2]-'0')*10+msn[3]-'0';
    int r1=msn[4]-'0';
    int r2=msn[5]-'0';
    int r3=msn[6]-'0';

    for(int i=7;i<10;i++)
        ir+=msn[i];

    for(int i=10;i<13;i++)
        lr+=msn[i];

    for(int i=13;i<15;i++)
        st+=msn[i];

    int clavec=(msn[15]-'0')*10+msn[16]-'0';

    for(int i=17;i<msn.size();i++)
        decypher+=msn[i];

    afin a2(a,b);
    decypher=a2.descifrado(decypher);

    enigma e2(r1,r2,r3,ir,lr,st);
    decypher=e2.descifrado(decypher);

    cesar c2(clavec);
    decypher=c2.descifrado(decypher);

    escribir("descifrado.txt",decypher);

    cout<<a<<" "<<b<<" "<<r1<<" "<<r2<<" "<<r3<<" "<<ir<<" "<<lr<<" "<<st<<" "<<clavec<<endl;

}
