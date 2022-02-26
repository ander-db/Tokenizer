#include <iostream>
#include <string>
#include <list>
#include "tokenizador.h"
#include <chrono>

using namespace std;

///////// Comprobaci�n de que vac�e la lista resultado

void imprimirListaSTL(const list<string> &cadena)
{
        list<string>::const_iterator itCadena;
        for (itCadena = cadena.begin(); itCadena != cadena.end(); itCadena++)
        {
                cout << (*itCadena) << ", ";
        }
        cout << endl;
}

int main(void)
{

        Tokenizador a(".,-@#", true, false);
        string test1 = "test@ander@em@ail.com";
        list<string> tokens;
        cout << a << endl;

        a.Tokenizar(test1, tokens);
        

        imprimirListaSTL(tokens);



        return 0;
}
