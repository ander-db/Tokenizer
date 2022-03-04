#include "tokenizador.h"

// TODO: Probar usar nmap para leer archivo

/**
 * @brief Matriz automata.
 *
 */
const unsigned char Tokenizador::TP_AUTOMATA[45][17] = {
	{20, 21, 0, 0, 0, 0, 0, 0, 0, 12, 26, 27, 1, 1, 1, 1, 1},  // Nodo 0
	{4, 39, 5, 3, 39, 39, 39, 39, 39, 2, 2, 2, 2, 2, 2, 2, 2}, // Nodo 1
	{4, 39, 5, 3, 39, 39, 39, 39, 39, 2, 2, 2, 2, 2, 2, 2, 2}, // Nodo 2
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 6, 6, 6, 6, 6, 6, 6, 6},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 8, 8, 8, 8, 8, 8, 8, 8},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 9, 9, 9, 9, 9, 9, 9, 9}, // Nodo 5
	{7, 39, 7, 37, 39, 7, 39, 39, 39, 6, 6, 6, 6, 6, 6, 6, 6},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 6, 6, 6, 6, 6, 6, 6},
	{10, 39, 39, 39, 39, 39, 39, 39, 39, 8, 8, 8, 8, 8, 8, 8, 8}, // Nodo 8
	{39, 39, 11, 39, 39, 39, 39, 39, 39, 9, 9, 9, 9, 9, 9, 9, 9}, // Nodo 9
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 8, 8, 8, 8, 8, 8, 8, 8},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 9, 9, 9, 9, 9, 9, 9, 9}, // Grafo inferior

	{14, 15, 5, 3, 39, 39, 39, 39, 39, 13, 2, 2, 2, 2, 2, 2, 2}, // Nodo 12
	{14, 15, 5, 3, 39, 39, 39, 39, 39, 13, 2, 2, 2, 2, 2, 2, 2},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 16, 8, 8, 8, 8, 8, 8, 8},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 17, 38, 38, 38, 38, 38, 38, 38},
	{19, 18, 39, 39, 39, 39, 39, 39, 39, 16, 8, 8, 8, 8, 8, 8, 8}, // nodo e16
	{18, 18, 39, 39, 43, 39, 39, 39, 39, 17, 37, 37, 37, 37, 37, 37, 37},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 17, 37, 37, 37, 37, 37, 37, 37},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 16, 8, 8, 8, 8, 8, 8, 8},

	{20, 21, 0, 0, 0, 0, 0, 0, 0, 22, 1, 1, 1, 1, 1, 1, 1}, // nodo 20
	{20, 21, 0, 0, 0, 0, 0, 0, 0, 23, 1, 1, 1, 1, 1, 1, 1},
	{24, 25, 41, 41, 43, 41, 41, 41, 41, 22, 42, 42, 42, 42, 42, 42, 42},
	{25, 25, 41, 41, 34, 41, 41, 41, 41, 23, 42, 42, 42, 42, 42, 42, 42},
	{40, 40, 40, 40, 40, 32, 40, 40, 40, 22, 42, 42, 42, 42, 42, 42, 42},
	{40, 40, 40, 40, 40, 32, 40, 40, 40, 23, 42, 42, 42, 42, 42, 42, 42},

	{4, 38, 5, 3, 38, 38, 38, 38, 38, 2, 2, 2, 28, 2, 2, 2, 2},			  // Nodo 26
	{4, 38, 5, 3, 38, 38, 38, 38, 38, 2, 2, 2, 29, 2, 2, 2, 2},			  // Nodo 27
	{4, 38, 5, 3, 38, 38, 38, 38, 38, 2, 2, 2, 30, 2, 2, 2, 2},			  // Nodo 28
	{4, 38, 5, 3, 38, 38, 38, 38, 38, 2, 2, 2, 31, 2, 2, 2, 2},			  // Nodo 29
	{4, 38, 5, 3, 38, 38, 38, 38, 38, 2, 2, 2, 2, 32, 2, 2, 2},			  // Nodo 30
	{4, 38, 5, 3, 38, 38, 38, 38, 38, 2, 2, 2, 2, 33, 2, 2, 2},			  // Nodo 31
	{4, 38, 5, 3, 38, 38, 35, 38, 38, 2, 2, 2, 2, 2, 34, 44, 2},		  // Nodo 32
	{4, 39, 5, 3, 39, 39, 35, 39, 39, 2, 2, 2, 2, 2, 3, 44, 2},			  // Nodo 33
	{4, 39, 5, 3, 39, 39, 35, 39, 39, 2, 2, 2, 2, 2, 34, 44, 2},		  // Nodo 34
	{36, 38, 36, 36, 36, 38, 36, 36, 38, 36, 36, 36, 36, 36, 36, 36, 36}, // Nodo 35
	{36, 39, 36, 36, 36, 39, 36, 36, 39, 36, 36, 36, 36, 36, 36, 36, 36}, // Nodo 36

	{37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37},
	{38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38},
	{39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 49, 39, 39, 39},
	{40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40},
	{41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41},
	{42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42},
	{43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43},

	{36, 39, 36, 36, 36, 39, 36, 36, 39, 36, 36, 36, 36, 36, 36, 36, 36}, // Nodo 44
};

// TODO: Comprobar cuanto tarda en ejecutarse este codigo en el ordenador de clase.
/**
 * @brief Inicializa delimiters a delimitadoresPalabra filtrando que no se  introduzcan delimitadores repetidos (de izquierda a derecha, en cuyo  caso se eliminarían los que hayan sido repetidos por la derecha); casosEspeciales a kcasosEspeciales; pasarAminuscSinAcentos a minuscSinAcentos
 *
 * @param delimitadoresPalabra Delimitadores de tokens
 * @param kcasosEspeciales Casos especiales
 * @param minuscSinAcentos Pasar a minuscula sin acentos
 */
Tokenizador::Tokenizador(const string &delimitadoresPalabra, const bool &kcasosEspeciales, const bool &minuscSinAcentos)
{
	this->delimiters = eliminarCaracteresRepetidos(delimitadoresPalabra);
	this->delimitadoresEspeciales = eliminarCaracteresRepetidos(this->delimiters + " \n");
	this->casosEspeciales = kcasosEspeciales;
	this->pasarAminuscSinAcentos = minuscSinAcentos;
}

/**
 * @brief Constructor de copia
 *
 * @param tokenizador Tokenizador a copiar.
 */
Tokenizador::Tokenizador(const Tokenizador &tokenizador)
{
	this->delimiters = tokenizador.delimiters;
	this->casosEspeciales = tokenizador.casosEspeciales;
	this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;
}

/**
 * @brief Constructor por defecto. Delimitadores por defecto, casosEspciales = true y pasarAminuscSinAcentos = false;
 *
 */
Tokenizador::Tokenizador()
{
	this->delimiters = DEFAULT_DELIMETERS_STR_ORDENADO;
	this->delimitadoresEspeciales = DEFAULT_DELIMETERS_STR_ORDENADO;
	this->casosEspeciales = true;
	this->pasarAminuscSinAcentos = false;
}

/**
 * @brief Destructor de la clase Tokenizador. Establece delimiters a "".
 *
 */
Tokenizador::~Tokenizador()
{
	// TODO: Preguntar que se hace con los bool, Los pasamos a false?
	// this->delimiters.delimitadoresOrdenados.clear();
	// this->delimiters.delimitadoresOrdenados = "";
	this->delimiters = "";
	this->delimitadoresEspeciales = " \n";
}

/**
 * @brief Sobrecarga del operador copia.
 *
 * @param tokenizador Tokenizador a copiar.
 * @return Nuevo tokenizador.
 */
Tokenizador &Tokenizador::operator=(const Tokenizador &tokenizador)
{
	this->delimiters = tokenizador.delimiters;
	this->casosEspeciales = tokenizador.casosEspeciales;
	this->pasarAminuscSinAcentos = tokenizador.pasarAminuscSinAcentos;

	return *this;
}

/**
 * @brief Tokeniza str devolviendo el resultado en tokens. La lista tokens se  vaciará antes de almacenar el resultado de la tokenización.
 *
 * @param str String a tokenizar.
 * @param tokens Lista donde se almacenan los tokens de str.
 */
void Tokenizador::Tokenizar(const string &str, list<string> &tokens) const
{
	tokens.clear();
	string strCopy = str;
	if (this->pasarAminuscSinAcentos)
		for (int i = 0; i < strCopy.size(); ++i)
			minusculaSinAcento(strCopy[i]);

	if (this->casosEspeciales)
		TokenizarCasosEspeciales(strCopy, tokens);
	else
	{
		string::size_type lastPos = strCopy.find_first_not_of(delimiters, 0);
		string::size_type pos = strCopy.find_first_of(delimiters, lastPos);
		while (string::npos != pos || string::npos != lastPos)
		{
			tokens.push_back(strCopy.substr(lastPos, pos - lastPos));
			lastPos = strCopy.find_first_not_of(this->delimiters, pos);
			pos = strCopy.find_first_of(this->delimiters, lastPos);
		}
	}
}

bool Tokenizador::TokenizarOptimizado(string &str) const
{
	if (this->pasarAminuscSinAcentos)
		for (int i = 0; i < str.size(); ++i)
			minusculaSinAcento(str[i]);

	if (this->casosEspeciales)
		TokenizarCasosEspeciales(str);
	else
	{
		string::size_type lastPos = str.find_first_of(delimiters, 0);
		string::size_type pos = str.find_first_not_of(delimiters, lastPos);
		while (string::npos != pos || string::npos != lastPos)
		{
			str.replace(lastPos, pos - lastPos, "\n");
			lastPos = str.find_first_of(this->delimiters, pos);
			pos = str.find_first_not_of(this->delimiters, lastPos);
		}
	}

	return true;
}

/**
 * @brief Tokeniza el fichero i guardando la salida en el fichero f (una  palabra en cada línea del fichero). Devolverá true si se realiza la  tokenización de forma correcta; false en caso contrario enviando a cerr  el mensaje correspondiente (p.ej. que no exista el archivo i)
 *
 * @param i Fichero a tokenizar.
 * @param f Fichero donde se guarda i tokenizado.
 * @return true Si se realizar la tokenizacion de forma correcta.
 * @return false Si no se realiza la tokenizacoin de forma correcta (p. ej. que no existe el archivo i)
 */
bool Tokenizador::Tokenizar(const string &NomFichEntr, const string &NomFichSal) const
{
	/*
	ifstream i;
	ofstream f;
	string cadena;
	list<string> tokens;
	i.open(NomFichEntr.c_str());
	if (!i)
	{
		cerr << "ERROR: No existe el archivo: " << NomFichEntr << endl;
		return false;
	}
	else
	{
		std::getline(std::ifstream(NomFichEntr), cadena, '\0');
		Tokenizar(cadena, tokens);
	}
	i.close();
	f.open(NomFichSal.c_str());
	list<string>::iterator itS;
	for (itS = tokens.begin(); itS != tokens.end(); itS++)
	{
		f << (*itS) << '\n';
	}
	f.close();
	return true;
	*/

	std::ifstream i(NomFichEntr);

	list<string> tokens;

	if (i)
	{
		i.seekg(0, std::ios::end);
		const auto size = i.tellg();

		std::string str(size, ' ');
		i.seekg(0);
		i.read(&str[0], size);

		Tokenizar(str, tokens);

		i.close();

		ofstream f;
		f.open(NomFichSal.c_str());
		list<string>::iterator itS;
		for (itS = tokens.begin(); itS != tokens.end(); itS++)
		{
			f << (*itS) << '\n';
		}
		f.close();

		// Operations on `str`...
	}
	else
	{
		cerr << "ERROR: No existe el archivo: " << NomFichEntr << endl;
		return false;
	}

	return true;
}

/**
 * @brief Tokeniza el fichero i guardando la salida en un fichero de nombre i añadiéndole extensión .tk (sin eliminar previamente la extensión de i por ejemplo, del archivo pp.txt se generaría el resultado en pp.txt.tk), y que contendrá una palabra en cada línea del fichero. Devolverá true si se realiza la tokenización de forma correcta; false en caso contrarioenviando a cerr el mensaje correspondiente (p.ej. que no exista el archivo i)
 *
 * @param i
 * @return true
 * @return false
 */
bool Tokenizador::Tokenizar(const string &NomFichEntr) const
{
	ifstream i;
	ofstream f;
	string cadena;
	list<string> tokens;
	i.open(NomFichEntr.c_str());
	if (!i)
	{
		cerr << "ERROR: No existe el archivo: " << NomFichEntr << endl;
		return false;
	}
	else
	{
		// ** Menos memoria. Mas Lento. 1412kb - 6 segs
		std::getline(i, cadena, '\0');
		Tokenizar(cadena, tokens);
	}
	i.close();
	f.open((NomFichEntr + ".tk").c_str());
	list<string>::iterator itS;
	for (itS = tokens.begin(); itS != tokens.end(); itS++)
	{
		f << (*itS) << '\n';
	}
	f.close();
	return true;
}

void Tokenizador::TokenizarCasosEspeciales(const std::string &cadena, list<string> &tokens) const
{
	size_t principio = 0, final_ = 0;
	int i = 0;
	string cadenaTokens;
	short currentState = 0;

	while (cadena[i] != '\0')
	{
		nextState(currentState, cadena[i]);
		updateTokens(currentState, cadena, cadenaTokens, principio, final_, i);
		++i;
	}

	nextState(currentState, '\n');
	updateTokens(currentState, cadena, cadenaTokens, principio, final_, i);

	cadenaAListaTokens(cadenaTokens, tokens);
}

void Tokenizador::TokenizarCasosEspeciales(std::string &cadena) const
{
	size_t principio = 0, final_ = 0;
	int i = 0;
	string cadenaTokens;
	short currentState = 0;
	size_t end = cadena.size();

	while (i < end)
	{
		nextState(currentState, cadena[i]);
		updateTokens(currentState, cadena, cadenaTokens, principio, final_, i);
		++i;
	}

	nextState(currentState, '\n');
	updateTokens(currentState, cadena, cadenaTokens, principio, final_, i);
	
	cadena = cadenaTokens;
}
/**
 * @brief Lectura y escritura con mmap. Modificado el metodo basico.
 *
 * @param NomFichEntr
 * @return true
 * @return false
 */
bool Tokenizador::TokenizarFicheroOptimizado(const string &NomFichEntr) const
{

	struct stat fileIn;

	int fdIn = open(NomFichEntr.c_str(), O_RDONLY, 777);
	ofstream salida(NomFichEntr + ".tk");

	if (stat(NomFichEntr.c_str(), &fileIn) == -1 || fstat(fdIn, &fileIn) == -1)
	{
		std::cerr << "No pude abrir el archivo\n";
		return false;
	}

	size_t fsize = fileIn.st_size; // <- Total size, in bytes

	void *addrRead = mmap(NULL, fsize, PROT_EXEC, MAP_SHARED, fdIn, 0); // Step 3 mapping
	if (addrRead == MAP_FAILED)
	{
		std::cerr << "No pude abrir el archivo\n";
		return false;
	}
#if 0
	string cadena((char *)addrRead);
	string cadena2((char *)addrRead);
	// cadena.reserve(fsize / 1.2);
	TokenizarBasicoOptimizado((char *)addrRead, cadena);
#endif

	string cadena((char *)addrRead);
	// cadena.reserve(fsize / 1.2);
	TokenizarOptimizado(cadena);

	// TokenizarBasicoOptimizado3((char*) addrRead, cadena);

	close(fdIn);

	salida.write(cadena.c_str(), cadena.size());
	salida.close();
	return true;
}

void Tokenizador::TokenizarBasicoOptimizado(const char *fileStr, std::string &cadena) const
{
	string::size_type lastPos = cadena.find_first_of(delimiters, 0);
	string::size_type pos = cadena.find_first_not_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		cadena.replace(lastPos, pos - lastPos, "\n");
		lastPos = cadena.find_first_of(this->delimiters, pos);
		pos = cadena.find_first_not_of(this->delimiters, lastPos);
	}
}

void Tokenizador::TokenizarBasicoOptimizado2(const char *fileStr, std::string &cadena) const
{
	size_t i = 0;
	while (this->delimiters.find(fileStr[i]) != string::npos)
	{
		++i;
	}

	while (fileStr[i] != '\0')
	{
		if (this->delimiters.find(fileStr[i]) != string::npos)
		{
			cadena.push_back('\n');
		}
		else if (i != 0 && fileStr[i - 1] != '\n' && fileStr[i - 1] != ' ')
			cadena.push_back(fileStr[i]);
		++i;
	}
}

void Tokenizador::TokenizarCasosEspeciales2(const char *fileStr, std::string &cadena) const
{
	int i = 0;
	size_t principio = 0, final_ = 0;
	short currentState = 0;

	while (fileStr[i] != '\0')
	{
		nextState(currentState, fileStr[i]);
		updateTokens(currentState, fileStr, cadena, principio, final_, i);
	}

	nextState(currentState, '\n');
	updateTokens(currentState, fileStr, cadena, principio, final_, i);
}

void Tokenizador::TokenizarCasosEspeciales3(const char *fileStr, std::string &cadena, list<string> &tokens) const
{
	int i = 0;
	size_t principio = 0, final_ = 0;
	short currentState = 0;

	while (fileStr[i] != '\0')
	{
		nextState(currentState, fileStr[i]);
		updateTokens(currentState, fileStr, cadena, principio, final_, i);
	}

	nextState(currentState, '\n');
	updateTokens(currentState, fileStr, cadena, principio, final_, i);
}

void Tokenizador::cadenaAListaTokens(const string &cadena, list<string> &tokens) const
{
	string::size_type lastPos = cadena.find_first_not_of('\n', 0);
	string::size_type pos = cadena.find_first_of('\n', lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(cadena.substr(lastPos, pos - lastPos));
		lastPos = cadena.find_first_not_of('\n', pos);
		pos = cadena.find_first_of('\n', lastPos);
	}
}

/**
 * @brief Actualiza el valor del estado actual.
 *
 * @param currentState Estado actual.
 * @param character Caracter para calcular el siguiente estado.
 */
void Tokenizador::nextState(short &currentState, const char &caracter) const
{
	currentState = TP_AUTOMATA[currentState][calcularConjunto(caracter)];
}

/**
 * @brief Actualiza los tokens segun el estado actual.
 *
 * @param currentState Estado actual
 * @param cadena Cadena a tokenizar
 * @param cadenaTokens Cadena con los tokens separados por saltos de linea
 * @param principio Principio del token
 * @param final Final del token
 */
void Tokenizador::updateTokens(short &currentState, const char *cadena, std::string &cadenaTokens, size_t &principio, size_t &final_, int &currentPos) const
{
	switch (currentState)
	{
	case 38:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;

	case 39:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 40:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 41:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 42:
		currentPos = principio + 1;
		currentState = 0;
		break;

	case 43:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back(' ');
		cadenaTokens.push_back(cadena[currentPos]);
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 37:
		break;

	case 1:
	case 12:
	case 20:
	case 21:
	case 26:
	case 27:
		principio = currentPos;
		break;

	case 3:
	case 14:
	case 15:
	case 24:
	case 25:
		final_ = currentPos;

	default:
		break;
	}
}

void Tokenizador::updateTokens(short &currentState, const string &cadena, std::string &cadenaTokens, size_t &principio, size_t &final_, int &currentPos) const
{
	switch (currentState)
	{
	case 38:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
		--currentPos;
		break;

	case 39:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		--currentPos;
		break;
	case 40:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
		--currentPos;
		break;
	case 41:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		--currentPos;
		break;
	case 42:
		currentPos = principio;
		currentState = 0;
		break;

	case 43:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back(' ');
		cadenaTokens.push_back(cadena[currentPos]);
		cadenaTokens.push_back('\n');
		currentState = 0;
		--currentPos;
		break;
	case 37:

		cadenaTokens.append(std::string(cadena, principio, final_ - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		currentPos = final_;
		--currentPos;
		break;

	case 1:
	case 12:
	case 20:
	case 21:
	case 26:
	case 27:
		principio = currentPos;
		break;

	case 3:
	case 14:
	case 15:
	case 24:
	case 25:
		final_ = currentPos;

	default:
		break;
	}
}

/**
 * @brief  Tokeniza el fichero i que contiene un nombre de fichero por línea guardando la salida en ficheros (uno por cada línea de i) cuyo nombre será el leído en i añadiéndole extensión .tk, y que contendrá una palabra en cada línea del fichero leído en i. Devolverá true si se realiza la tokenización de forma correcta de todos los archivos que contiene i; devolverá false en caso contrario enviando a cerr el mensaje correspondiente (p.ej. que no exista el archivo i, o que se trate de un directorio, enviando a “cerr” los archivos de i que no existan o que sean directorios; luego no se ha de interrumpir la ejecución si hay algún archivo en i que no exista)
 *
 * @param i Fichero con lista de ficheros a tokenizar.
 * @return true Se han podido tokenizar los archivos de i con exito.
 * @return false Si no se ha podido tokenizar con exito. P.ej. No existen los directorios de i.
 */
bool Tokenizador::TokenizarListaFicheros(const string &NomFichEntr) const
{
	// TODO: Cmabiar nombres variables para entenderlo mejor.
	ifstream i;
	ofstream f;
	string cadena;
	list<string> tokens;
	i.open(NomFichEntr.c_str());
	if (!i)
	{
		cerr << "ERROR: No existe el archivo: " << NomFichEntr << endl;
		return false;
	}
	else
	{

		while (!i.eof())
		{
			cadena = "";
			getline(i, cadena);
			if (cadena.length() != 0)
			{
				// Tokenizar(cadena);
				TokenizarFicheroOptimizado(cadena);
			}
		}
	}
	return false;
}

/**
 * @brief Tokeniza todos los archivos que contenga el directorio i, incluyendo los de los subdirectorios, guardando la salida en ficheros cuyo nombre será el de entrada añadiéndole extensión .tk, y que contendrá una palabra en cada línea del fichero.
 *
 * @param i Directorio
 * @return true Se ha realizado la tokenizacion de forma correcta de los archivos del directorio i.
 * @return false No se ha podido realizar la tokenizacion. P.ej. No existe el directorio i
 */
bool Tokenizador::TokenizarDirectorio(const string &dirAIndexar) const
{
	struct stat dir;
	// Compruebo la existencia del directorio
	int err = stat(dirAIndexar.c_str(), &dir);
	if (err == -1 || !S_ISDIR(dir.st_mode))
		return false;
	else
	{
		// Hago una lista en un fichero con find>fich
		string cmd = "find " + dirAIndexar + " -type f -follow > .lista_fich";
		system(cmd.c_str());
		return TokenizarListaFicheros(".lista_fich");
	}
}

/**
 * @brief Cambia “delimiters” por “nuevoDelimiters” comprobando que no hayan delimitadores repetidos (de izquierda a derecha), en cuyo caso se eliminarían los que hayan sido repetidos (los nuevos delimitadores que se van analizando) tanto en “nuevoDelimiters” como los que ya estuviesen en “delimiters”
 *
 * @param nuevoDelimiters Nuevos delimitadores
 */
void Tokenizador::DelimitadoresPalabra(const string &nuevoDelimiters)
{
	this->delimiters = eliminarCaracteresRepetidos(nuevoDelimiters);
	this->delimitadoresEspeciales = eliminarCaracteresRepetidos(this->delimiters + " \n");
}

/**
 * @brief Añade al final de “delimiters” los nuevos delimitadores que aparezcan en “nuevoDelimiters” (no se almacenarán caracteres repetidos)
 *
 * @param nuevoDelimiters Delimiter a añadir.
 */
void Tokenizador::AnyadirDelimitadoresPalabra(const string &nuevoDelimiters)
{
	for (auto it = nuevoDelimiters.begin(); it != nuevoDelimiters.end(); ++it)
	{
		if (this->delimiters.find(*it) == string::npos)
			this->delimiters += *it;
	}

	this->delimitadoresEspeciales = eliminarCaracteresRepetidos(this->delimiters + " \n");
}

/**
 * @brief Getter de la variable "delimiters".
 *
 * @return Delimiters
 */
string Tokenizador::DelimitadoresPalabra() const
{
	// return this->delimiters.delimitadoresOrdenados;
	return this->delimiters;
}

/**
 * @brief Setter de la variable casosEspeciales
 *
 * @param nuevoCasosEspeciales Nuevo casos especiales
 */
void Tokenizador::CasosEspeciales(const bool &nuevoCasosEspeciales)
{

	this->casosEspeciales = nuevoCasosEspeciales;
}

/**
 * @brief Getter de casos especiales
 */
bool Tokenizador::CasosEspeciales() const
{
	return this->casosEspeciales;
}

/**
 * @brief Setter de la variable pasarAminuscSinAcentos
 *
 * @param nuevoPasarAminuscSinAcentos Nuevo valor de pasarAmunuscSinAcentos
 */
void Tokenizador::PasarAminuscSinAcentos(const bool &nuevoPasarAminuscSinAcentos)
{
	this->pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

/**
 * @brief Getter de pasarAminuscSinAcentos
 */
bool Tokenizador::PasarAminuscSinAcentos() const
{
	return this->pasarAminuscSinAcentos;
}

/**
 * @brief Elimina los caracteres repetidos de cadena.
 *
 * @param cadena Cadena a eliminar los caracteres repetidos
 */
string Tokenizador::eliminarCaracteresRepetidos(const string &cadena)
{
	string res = "";

	for (auto it = cadena.begin(); it != cadena.end(); ++it)
	{
		if (res.find(*it) == string::npos)
			res += *it;
	}

	return res;
}

/**
 * @brief Aunque se modifique el almacenamiento de los delimitadores por temas  de eficiencia, el campo delimiters se imprimirá con el string leído en  el tokenizador (tras las modificaciones y eliminación de los caracteres repetidos correspondientes)
 */
ostream &operator<<(ostream &os, const Tokenizador &tok)
{
	os << "DELIMITADORES: " << tok.DelimitadoresPalabra() << " TRATA CASOS ESPECIALES: " << tok.CasosEspeciales() << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tok.PasarAminuscSinAcentos();
	return os;
}

/**
 * @brief Modifica el caracter y lo pasa a minuscula.
 *
 * @param caracter Caracter a modificar.
 */
void Tokenizador::minusculaSinAcento(char &caracter) const
{
	if ((unsigned char)caracter >= 0x41 && (unsigned char)caracter <= 0x5a)
	{
		caracter += 32;
	}
	else if (((unsigned char)caracter >= 0xc0 && (unsigned char)caracter <= 0xc5) || ((unsigned char)caracter >= 0xe0 && (unsigned char)caracter <= 0xe5)) // A
	{
		caracter = (unsigned char)0x61;
	}
	else if (((unsigned char)caracter >= 0xc8 && (unsigned char)caracter <= 0xcb) || ((unsigned char)caracter >= 0xe8 && (unsigned char)caracter <= 0xeb)) // E
	{
		caracter = (unsigned char)0x65;
	}
	else if (((unsigned char)caracter >= 0xcc && (unsigned char)caracter <= 0xcf) || ((unsigned char)caracter >= 0xec && (unsigned char)caracter <= 0xef)) // I
	{
		caracter = (unsigned char)0x69;
	}
	else if (((unsigned char)caracter >= 0xd2 && (unsigned char)caracter <= 0xd6) || ((unsigned char)caracter >= 0xf2 && (unsigned char)caracter <= 0xf6)) // O
	{
		caracter = (unsigned char)0x6f;
	}
	else if (((unsigned char)caracter >= 0xd9 && (unsigned char)caracter <= 0xdc) || ((unsigned char)caracter >= 0xf9 && (unsigned char)caracter <= 0xfc)) // U
	{
		caracter = (unsigned char)0x75;
	}
	else if ((unsigned char)caracter == 0xd1)
	{
		caracter = (unsigned char)0xf1;
	}
}

/**
 * @brief Almacena en conjunto, el conjunto al que pertenece el caracter.
 *
 * @param conjunto Conjunto
 * @param caracter Caracter
 */
unsigned char Tokenizador::calcularConjunto(const char &caracter) const
{

	if (this->delimitadoresEspeciales.find(caracter) != string::npos)
	{
		switch (caracter)
		{
		case '.':
			return 0;
		case ',':
			return 1;
		case '-':
			return 2;
		case '@':
			return 3;
		case '%':
		case '$':
			return 4;

		case '_':
			return 5;

		case ':':
			return 6;
		case '/':
		case '?':
		case '&':
		case '=':
		case '#':
			return 7;

		default:
			return 8;
		}
	}

	else
	{
		switch (caracter)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return 9;
		case 'h':
			return 10;
		case 'f':
			return 11;
		case 't':
			return 12;
		case 'p':
			return 13;
		case 's':
			return 14;
		case ':':
			return 15;
		case '%':
		case '$':
			return 4;
		default:
			return 16;
		}
	}
}
