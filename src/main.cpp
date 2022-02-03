#include <iostream>
#include <string>
#include <list>

#include "../include/tokenizador.h"


using namespace std;

int main()
{

	list<string> tokens;
	string ficheroEntrada = "pruebafichero1.txt";
	string ficheroSalida = "pruebafichero1Salida.txt";

	string str1 = "hola-buenos?¿?!dias-//como)(estas?";
	Tokenizador tok1 = Tokenizador();
	Tokenizador tok2 = Tokenizador();


	tok1.DelimitadoresPalabra("abcde");
	tok2 = tok1;
	cout << tok1.DelimitadoresPalabra() << endl;
	cout << tok2.DelimitadoresPalabra() << endl;
	
	tok1.CasosEspeciales(false);

	tok2.AnyadirDelimitadoresPalabra("f");
	tok2.AnyadirDelimitadoresPalabra("f");
	

	cout << tok1 << endl;
	cout << tok2 << endl;
	

	return 0;
}