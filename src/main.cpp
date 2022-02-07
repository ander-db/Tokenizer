#include <iostream>
#include <memory>
#include "../include/tokenizador.h"
#include <list>
#include <chrono>

using namespace std;

int main()
{
	Tokenizador tok1;
	list<string> tokens;

	auto start = std::chrono::system_clock::now();


	tok1.TokenizarListaFicheros("listaFicheros.txt");

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<float,std::milli> duration = end - start;
    std::cout << duration.count() << "ms " << std::endl;


	return 0;
}