#ifndef TOKENIZADOR_H_
#define TOKENIZADOR_H_

#include <iostream>
#include <ostream>
#include <string>
#include <list>

using namespace std;

static const string DEFAULT_DELIMETERS = ",;:.-/+*\\'\"{}[]()<>¡!¿?&#=\t\n\r@";

class Tokenizador
{
	friend ostream &operator<<(ostream &, const Tokenizador &);
	// cout << “DELIMITADORES: “ << delimiters << “ TRATA CASOS ESPECIALES: “ << casosEspeciales << “ PASAR A MINUSCULAS Y SIN ACENTOS: “ <<  pasarAminuscSinAcentos;
	// Aunque se modifique el almacenamiento de los delimitadores por temas  de eficiencia, el campo delimiters se imprimirá con el string leído en  el tokenizador (tras las modificaciones y eliminación de los caracteres  repetidos correspondientes)

private:
	string delimiters; // Delimitadores de términos. Aunque se modifique la forma de almacenamiento interna para mejorar la eficiencia, este campo debe permanecer para indicar el orden en que se introdujeron los delimitadores

	bool casosEspeciales;
	// Si true detectará palabras compuestas y casos especiales. Sino, trabajará al igual que el algoritmo propuesto en la sección “Versión del tokenizador vista en clase”

	bool pasarAminuscSinAcentos;
	// Si true pasará el token a minúsculas y quitará acentos, antes de realizar la tokenización

public:
	Tokenizador(const string &delimitadoresPalabra, const bool &kcasosEspeciales, const bool &minuscSinAcentos);

	Tokenizador(const Tokenizador &);

	Tokenizador();

	~Tokenizador(); 

	Tokenizador &operator=(const Tokenizador &);

	void Tokenizar(const string &str, list<string> &tokens) const;

	bool Tokenizar(const string &i, const string &f) const;

	bool Tokenizar(const string &i) const;

	bool TokenizarListaFicheros(const string &i) const;

	bool TokenizarDirectorio(const string &i) const;

	void DelimitadoresPalabra(const string &nuevoDelimiters);

	void AnyadirDelimitadoresPalabra(const string &nuevoDelimiters); //

	string DelimitadoresPalabra() const;

	void CasosEspeciales(const bool &nuevoCasosEspeciales);

	bool CasosEspeciales();

	void PasarAminuscSinAcentos(const bool &nuevoPasarAminuscSinAcentos);

	bool PasarAminuscSinAcentos();
};

#endif