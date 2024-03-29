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

struct Delimitadores
{
	std::unordered_set<char> mapDelimiters;
	std::string delimitadoresOrdenados;
};

struct TokenInfo
{
	vector<int> estado;
	vector<int> principioToken;
	vector<int> finalToken;
};

/**
 * @brief Delimitadores por defecto.
 *
 */
static const string DEFAULT_DELIMETERS_STR_ORDENADO = ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";

/**
 * @brief Set desordenado de delimitadores por defecto.
 *
 */
static const std::unordered_set<char> DEFAULT_DELIMETERS_SET = unordered_set<char>(begin(DEFAULT_DELIMETERS_STR_ORDENADO), end(DEFAULT_DELIMETERS_STR_ORDENADO));

/**
 * @brief Estructura de los delimitadores por defecto (set de delimitadores y string ordenado).
 *
 */
static const Delimitadores DEFAULT_STRUCT_DELIMITADORES{
	DEFAULT_DELIMETERS_SET,
	DEFAULT_DELIMETERS_STR_ORDENADO};

/**
 * @brief Set de caracteres que siempre delimitan
 *
 */
static const std::unordered_set<char> SIEMPRE_DELIMITAN_SET = {' ', '\n'};

/**
 * @brief String de caracteres que siempre delimitan.
 *
 */
static const string SIEMPRE_DELIMITAN_STR = "\\  \n";

/**
 * @brief Estructura de los delimitadores que siempre delimitan (aunque no se especifiquen)
 *
 */
static const Delimitadores SIEMPRE_DELIMITAN_STRUCT =
	{
		SIEMPRE_DELIMITAN_SET,
		SIEMPRE_DELIMITAN_STR};

static const string DAFAULT_CASOS_ESPECIALES_DELIMETERS = "\\ \n";
static const char CASO_ESPECIAL_GUIONES = '-';

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

	static const unsigned char TP_AUTOMATA[45][17];

	static string eliminarCaracteresRepetidos(const string &);

	unsigned char calcularConjunto(const char &) const;
	void nextState(short&, const char&) const;
	void updateTokens(short &, const char*, std::string &, size_t &, size_t &, int &) const;
	void updateTokens(short &, const string&, std::string &, size_t &, size_t &, int &) const;
	void minusculaSinAcento(char &) const;
	void cadenaAListaTokens(const string &, list <string> &) const;

public:


	Tokenizador(const string &delimitadoresPalabra, const bool &kcasosEspeciales, const bool &minuscSinAcentos);

	Tokenizador(const Tokenizador &);

	Tokenizador();

	~Tokenizador();

	Tokenizador &operator=(const Tokenizador &);

	void Tokenizar(const string &str, list<string> &tokens) const;

	bool Tokenizar(const string &i, const string &f) const;

	bool Tokenizar(const string &i) const;

	bool TokenizarFicheroOptimizado(const string &i) const;

	void TokenizarBasicoOptimizado(const char* fileStr, string &cadena)  const;
	void TokenizarBasicoOptimizado2(const char* fileStr, string &cadena)  const;
	void TokenizarCasosEspeciales2(const char* fileStr, string &cadena)  const;
	void TokenizarCasosEspeciales3(const char* fileStr, string &cadena, list <string> &tokens)  const;

	// TODO
	void TokenizarCasosEspeciales(const std::string &, list<string> &) const;

	// TODO
	bool TokenizarFicheroCasosEspeciales(const std::string &, const std::ofstream &) const;

	bool TokenizarListaFicheros(const string &i) const;

	bool TokenizarDirectorio(const string &i) const;

	void DelimitadoresPalabra(const string &nuevoDelimiters);

	void AnyadirDelimitadoresPalabra(const string &nuevoDelimiters);

	string DelimitadoresPalabra() const;

	void CasosEspeciales(const bool &nuevoCasosEspeciales);

	bool CasosEspeciales() const;

	void PasarAminuscSinAcentos(const bool &nuevoPasarAminuscSinAcentos);

	bool PasarAminuscSinAcentos() const;
};

#endif