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
        bool kCasosEspeciales = true, kpasarAminusculas = false;

        list<string> lt1, lt2;

        Tokenizador a(".-#", true, false);
        list<string> tokens;
        auto start = std::chrono::system_clock::now();
        a.Tokenizar("AA-U.S.A-B-C#A-B.C.D-AA-U.S.A-B-C#A-B.C.D-AA-U.S.A-B-C#A-B.C.D-AA-U.S.A-B-C#A-B.C.D-AA-U.S.A-B-C#A-B.C.D-AA-U.S.A-B-C#A-B.C.D-", tokens);
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<float, std::milli> duration = end - start;
        //std::cout << duration.count() << "ms " << std::endl;
        imprimirListaSTL(tokens);

        a.Tokenizar("--ANDER-DORADO-A--A", tokens);
        imprimirListaSTL(tokens);

        a.Tokenizar("ANDER-DO.RADO--A", tokens);
        imprimirListaSTL(tokens);
}
