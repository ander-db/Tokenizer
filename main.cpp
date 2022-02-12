#include <iostream>
#include <memory>
#include "../include/tokenizador.h"
#include <list>
#include <chrono>

using namespace std;

int main()
{

	list<string> tokens;
	string test1 = "a-d#a-#-a-b#c-s a- b";
	string delimitadores = "-# \n";
	Tokenizador tok1(delimitadores, true, true);
	



	tok1.TokenizarCasosEspeciales(test1, tokens);


	for(auto token : tokens)
	{
		cout << token << endl;
	}

	return 0;
}