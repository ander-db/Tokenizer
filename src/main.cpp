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

        Tokenizador a;
        list<string> tokens;
        auto start = std::chrono::system_clock::now();
        a.TokenizarListaFicheros("listaFicheros.txt");
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<float, std::milli> duration = end - start;
        std::cout << duration.count() << "ms " << std::endl;

        return 0;
}
