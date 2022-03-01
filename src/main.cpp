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

        Tokenizador a;
        a.CasosEspeciales(true);
        string test1 = "https://ander.com!";
        list<string> tokens;

        a.Tokenizar(test1, tokens);

        imprimirListaSTL(tokens);

        cout << a << endl;
        

#if 0
        // a.Tokenizar(test1, tokens);
        auto start = std::chrono::system_clock::now();
        a.TokenizarListaFicheros("listaFicheros.txt");
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<float, std::milli> duration = end - start;
        std::cout << duration.count() << "s" << std::endl;
        // imprimirListaSTL(tokens);
#endif

        return 0;
}
