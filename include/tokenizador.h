#ifndef TOKENIZADOR_H_
#define TOKENIZADOR_H_

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <list>
#include <unordered_set>
#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include <memory>
#include <xmmintrin.h> // Ensamblador
#include <vector>
#include <map>
#include <ctype.h>
#include <stdio.h>
#include <cstdint>
#include <cstring>

#include <sys/mman.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define PERM 0644
using namespace std;

/**
 * @brief Estructura que almacena un set de los delimitadores,
 * y un string de los delimitadores ordenados.
 *
 */

class Tokenizador
{

	friend ostream &operator<<(ostream &, const Tokenizador &);
	// cout << “DELIMITADORES: “ << delimiters << “ TRATA CASOS ESPECIALES: “ << casosEspeciales << “ PASAR A MINUSCULAS Y SIN ACENTOS: “ <<  pasarAminuscSinAcentos;
	// Aunque se modifique el almacenamiento de los delimitadores por temas  de eficiencia, el campo delimiters se imprimirá con el string leído en  el tokenizador (tras las modificaciones y eliminación de los caracteres  repetidos correspondientes)

private:
	static const unsigned char TP_AUTOMATA[45][17];

	/**
	 * @brief Delimitadores por defecto.
	 *
	 */
	static const string DEFAULT_DELIMETERS_STR_ORDENADO;

	/**
	 * @brief Delimitadores de terminos. Aunque se modifique la forma de almacenamiento interna para mejorar la eficiencia, este campo debe permanecer para indicar el orden en que se introdujeron los delimitadores.
	 *
	 */
	string delimiters;

	/**
	 * @brief Delimitadores para casos especiales.
	 *
	 */
	string delimitadoresEspeciales;

	/**
	 * @brief  Delimitadores de terminos. Almacena el caracter y la posicion
	 *
	 */
	// Delimitadores delimiters;

	/**
	 * @brief Si true detectará palabras compuestas y casos especiales. Sino, trabajará al igual que el algoritmo propuesto en la sección “Versión del tokenizador vista en clase”
	 *
	 */
	bool casosEspeciales;

	/**
	 * @brief Si true pasará el token a minúsculas y quitará acentos, antes de realizar la tokenización
	 *
	 */
	bool pasarAminuscSinAcentos;

	static string eliminarCaracteresRepetidos(const string &);

	unsigned char calcularConjunto(const char &) const;

	/**
	 * @brief Actualiza el valor del estado actual.
	 *
	 * @param currentState Estado actual.
	 * @param character Caracter para calcular el siguiente estado.
	 */
	void nextState(short &currentState, const char &caracter) const
	{
		currentState = TP_AUTOMATA[currentState][calcularConjunto(caracter)];
	}

	void updateTokens(short &, const char *, std::string &, size_t &, size_t &, int &) const;
	void updateTokens(short &, const string &, std::string &, size_t &, size_t &, int &) const;
	void minusculaSinAcento(char &) const;
	void cadenaAListaTokens(const string &, list<string> &) const;

	void TokenizarCasosEspeciales(const std::string &, list<string> &) const;
	void TokenizarCasosEspeciales(std::string &) const;

public:
	Tokenizador(const string &delimitadoresPalabra, const bool &kcasosEspeciales, const bool &minuscSinAcentos);

	Tokenizador(const Tokenizador &);

	Tokenizador();

	~Tokenizador();

	Tokenizador &operator=(const Tokenizador &);

	void Tokenizar(const string &str, list<string> &tokens) const;

	bool Tokenizar(const string &i, const string &f) const;

	bool Tokenizar(const string &i) const;

	bool TokenizarOptimizado(string &) const;

	bool TokenizarFicheroOptimizado(const string &i) const;

	bool TokenizarListaFicheros(const string &i) const;

	bool TokenizarDirectorio(const string &i) const;

	void DelimitadoresPalabra(const string &nuevoDelimiters);

	void AnyadirDelimitadoresPalabra(const string &nuevoDelimiters);

	/**
	 * @brief Getter de la variable "delimiters".
	 *
	 * @return Delimiters
	 */
	string DelimitadoresPalabra() const
	{
		return this->delimiters;
	}

	/**
	 * @brief Setter de la variable casosEspeciales
	 *
	 * @param nuevoCasosEspeciales Nuevo casos especiales
	 */
	void CasosEspeciales(const bool &nuevoCasosEspeciales)
	{

		this->casosEspeciales = nuevoCasosEspeciales;
	}

	/**
	 * @brief Getter de casos especiales
	 */
	bool CasosEspeciales() const
	{
		return this->casosEspeciales;
	}

	/**
	 * @brief Setter de la variable pasarAminuscSinAcentos
	 *
	 * @param nuevoPasarAminuscSinAcentos Nuevo valor de pasarAmunuscSinAcentos
	 */
	void PasarAminuscSinAcentos(const bool &nuevoPasarAminuscSinAcentos)
	{
		this->pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
	}

	/**
	 * @brief Getter de pasarAminuscSinAcentos
	 */
	bool PasarAminuscSinAcentos() const
	{
		return this->pasarAminuscSinAcentos;
	}
};

#endif