#include <iostream>
#include <string>
#include <list>

#include "../include/tokenizador.h"


using namespace std;

int main()
{

	Tokenizador tok1 = Tokenizador();
	cout << tok1 << endl;


	tok1.DelimitadoresPalabra("a-bc&*())/fg--_+");

	cout << tok1 << endl;
	

	return 0;
}