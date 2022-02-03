#include <iostream>
#include <string>
#include <list>

#include "tokenizador.h"
#include <string_view>

using namespace std;

int main()
{

	list<string> tokens;
	string ficheroEntrada = "pruebafichero1.txt";
	string ficheroSalida = "pruebafichero1Salida.txt";

	string str1 = "hola-buenos?¿?!dias-//como)(estas?";
	Tokenizador tok1 = Tokenizador();

	tok1.TokenizarListaFicheros("listaFicheros.txt");

	


	return 0;
}