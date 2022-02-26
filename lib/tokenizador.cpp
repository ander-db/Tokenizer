#include "tokenizador.h"

// TODO: Probar usar nmap para leer archivo

/**
 * @brief Matriz automata.
 *
 */
const unsigned char Tokenizador::TP_AUTOMATA[35][12] = {
	{20, 21, 0, 0, 0, 0, 0, 0, 12, 26, 27, 1},
	{4, 30, 5, 3, 30, 30, 30, 30, 2, 2, 2, 2},
	{4, 30, 5, 3, 30, 30, 30, 30, 2, 2, 2, 2},
	{29, 29, 29, 29, 29, 29, 29, 29, 6, 6, 6, 6},
	{29, 29, 29, 29, 29, 29, 29, 29, 8, 8, 8, 8},
	{29, 29, 29, 29, 29, 29, 29, 29, 9, 9, 9, 9},
	{7, 30, 7, 28, 30, 7, 30, 30, 6, 6, 6, 6},
	{29, 29, 29, 29, 29, 29, 29, 29, 6, 6, 6, 6},
	{10, 30, 30, 30, 30, 30, 30, 30, 8, 8, 8, 8},
	{30, 30, 11, 30, 30, 30, 30, 30, 9, 9, 9, 9},
	{29, 29, 29, 29, 29, 29, 29, 29, 8, 8, 8, 8},
	{29, 29, 29, 29, 29, 29, 29, 29, 9, 9, 9, 9}, // Grafo inferior

	{14, 15, 5, 3, 30, 30, 30, 30, 13, 2, 2, 2},
	{14, 15, 5, 3, 30, 30, 30, 30, 13, 2, 2, 2},
	{29, 29, 29, 29, 29, 29, 29, 29, 16, 8, 8, 8},
	{29, 29, 29, 29, 29, 29, 29, 29, 17, 29, 29, 29},
	{19, 18, 30, 30, 30, 30, 30, 30, 16, 8, 8, 8}, // nodo e16
	{18, 18, 30, 30, 34, 30, 30, 30, 17, 28, 28, 28},
	{29, 29, 29, 29, 29, 29, 29, 29, 17, 28, 28, 28},
	{29, 29, 29, 29, 29, 29, 29, 29, 16, 8, 8, 8},

	{20, 21, 0, 0, 0, 0, 0, 0, 22, 1, 1, 1}, // nodo 20
	{20, 21, 0, 0, 0, 0, 0, 0, 23, 1, 1, 1},
	{24, 25, 32, 32, 32, 34, 32, 22, 33, 33, 33},
	{25, 25, 32, 32, 32, 34, 32, 23, 33, 33, 33},
	{31, 31, 31, 31, 31, 31, 31, 22, 33, 33, 33},
	{31, 31, 31, 31, 31, 31, 31, 23, 33, 33, 33},

	{26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26},
	{27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27},

	{28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28},
	{29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29},
	{30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
	{31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},
	{32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32},
	{33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33},
	{34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34}};

/**
 * @brief Tabla de pesos para la deteccion mediante automata del caso acronimos.
 *
 */
const unsigned char Tokenizador::TP_MULTIPALABRA[6][3] = {{1, 0, 0},
														  {1, 2, 0},
														  {3, 0, 0},
														  {3, 4, 5},
														  {3, 5, 5},
														  {5, 5, 5}};

const unsigned char Tokenizador::TP_ACRONIMO[6][3] = {{1, 0, 0},
													  {0, 2, 0},
													  {3, 0, 0},
													  {5, 4, 5},
													  {3, 5, 5},
													  {5, 5, 5}};

/**
 * @brief Tabla de pesos para la deteccion mediante automata del caso basico.
 * //TODO: Borrar
 */
const unsigned char Tokenizador::TP_BASICO[3][2] = {{1, 0},
													{1, 2},
													{2, 2}};

/**
 * @brief Tabla de pesos para el caso especial Email
 *
 */
const unsigned char Tokenizador::TP_EMAIL[5][4] = {{1, 0, 0, 0},
												   {1, 2, 2, 0},
												   {3, 0, 0, 0},
												   {5, 4, 0, 4},
												   {5, 5, 5, 5}};
/**
 * @brief Tabla de pesos para el caso especial Numeros.
 *
 */
const unsigned char Tokenizador::TP_NUMERO[7][3] = {{1, 2, 0},
													{1, 2, 0},
													{4, 2, 0},
													{4, 0, 0},
													{4, 5, 6},
													{4, 6, 6},
													{6, 6, 6}};

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
	string stringDelimitadoresUnicos = delimitadoresPalabra;
	// eliminarCaracteresRepetidos(stringDelimitadoresUnicos);

	this->delimiters = delimitadoresPalabra + " \n";

	// this->delimiters.mapDelimiters = unordered_set<char>(begin(delimitadoresPalabra), end(delimitadoresPalabra));
	// this->delimiters.mapDelimiters.insert(' ');
	// this->delimiters.mapDelimiters.insert('\n');

	// this->delimiters.delimitadoresOrdenados = stringDelimitadoresUnicos;

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
	// this->delimiters = DEFAULT_STRUCT_DELIMITADORES;
	this->delimiters = DEFAULT_DELIMETERS_STR_ORDENADO;
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

	if (this->casosEspeciales)
		TokenizarCasosEspeciales(str, tokens);
	else
	{
		// TODO: Casos especiales
		string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		string::size_type pos = str.find_first_of(delimiters, lastPos);
		while (string::npos != pos || string::npos != lastPos)
		{
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			lastPos = str.find_first_not_of(this->delimiters, pos);
			pos = str.find_first_of(this->delimiters, lastPos);
		}
	}
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

#if 0 
void Tokenizador::TokenizarCasosEspeciales(const std::string &cadena, list<string> &tokens) const
{
	vector<char> vecCadena(cadena.begin(), cadena.end());
	vector<unsigned int> posCadena;
	posCadena.reserve(cadena.size());
	for (size_t i = 0; i < vecCadena.size(); ++i)
		posCadena.emplace_back(i);

	std::map<unsigned int, string> posTokens;

	// casoEspecialEmail(vecCadena, posCadena, posTokens);

	// if (this->delimiters.find(',') != string::npos || this->delimiters.find('.') != string::npos)
	//	casoEspecialNumero(vecCadena, posCadena, posTokens);
	if (this->delimiters.find('.') != string::npos)
		casoEspecialAcronimo(vecCadena, posCadena, posTokens);
	if (this->delimiters.find('-') != string::npos)
		casoEspecialMultipalabra(vecCadena, posCadena, posTokens);

	string aux(vecCadena.begin(), vecCadena.end());
	casoEspecialBasico(aux, posCadena, posTokens);

	// cout << "----" << endl;
	for (auto &value : posTokens)
	{
		// cout << value.first << '-' << value.second << endl;
		tokens.push_back(value.second);
	}
	// cout << "----" << endl;
}
#endif

void Tokenizador::TokenizarCasosEspeciales(const std::string &cadena, list<string> &tokens) const
{
	int i = 0;
	size_t principio = 0, final_ = 0;
	short currentState = 0;
	string cadenaTokens;

	while (cadena[i] != '\0')
	{
		nextState(currentState, cadena[i]);
		updateTokens(currentState, cadena, cadenaTokens, principio, final_, i);
		++i;
	}

	nextState(currentState, '\n');
	updateTokens(currentState, cadena, cadenaTokens, principio, final_, i);

	cout << "Soy el resultado:\n" << cadenaTokens << endl;
}

void Tokenizador::casoEspecialBasico(std::string &cadena, std::vector<unsigned int> &posiciones, std::map<unsigned int, string> &posTokens) const
{

	// TODO: Casos especiales
	string::size_type lastPos = cadena.find_first_not_of(delimiters, 0);
	string::size_type pos = cadena.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		// tokens.push_back(cadena.substr(lastPos, pos - lastPos));
		posTokens.insert({posiciones[lastPos], cadena.substr(lastPos, pos - lastPos)});

		lastPos = cadena.find_first_not_of(this->delimiters, pos);
		pos = cadena.find_first_of(this->delimiters, lastPos);
	}
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

	string cadena;

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

void Tokenizador::casoEspecialNumero(std::vector<char> &cadena, std::vector<unsigned int> &posiciones, std::map<unsigned int, string> &posTokens) const
{
	unsigned int iEnd = cadena.size();
	unsigned int principio = 0;
	unsigned int i = 0;
	unsigned int final = 0;
	unsigned char conjunto = 0;
	unsigned char estado = 0;

	string tokenNumero;

	while (i < cadena.size())
	{

		if (cadena[i] == '.' || cadena[i] == ',')
			conjunto = 1;
		else if (isdigit(cadena[i]))
			conjunto = 0;
		else
			conjunto = 2;

		switch (estado)
		{
		case 0:
			estado = TP_NUMERO[0][conjunto];
			break;
		case 1:
			estado = TP_NUMERO[1][conjunto];
			principio = i;
			break;
		case 2:
			estado = TP_NUMERO[2][conjunto];
			break;
		case 3:
			estado = TP_NUMERO[3][conjunto];
			break;
		case 4:
			estado = TP_NUMERO[4][conjunto];
			if (estado == 6)
			{
				final = i;
				estado = 0;
				tokenNumero = std::string(cadena.begin() + principio, cadena.begin() + final);
				procesarNumero(tokenNumero);
				posTokens.insert({posiciones[principio], tokenNumero});
				i = principio;
				if (principio != 0)
				{
					cadena.erase(cadena.begin() + principio, cadena.begin() + final + 1);
					posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final + 1);
					cadena[principio] = ' ';
				}
				else
				{
					cadena.erase(cadena.begin() + principio, cadena.begin() + final + 1);
					posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final + 1);
				}
				iEnd = cadena.size();
				continue;
			}
			break;
		case 5:
			estado = TP_NUMERO[5][conjunto];

			if (estado == 6)
			{
				final = i - 1; // Caso de que al final hay un -
				tokenNumero = std::string(cadena.begin() + principio, cadena.begin() + final);
				procesarNumero(tokenNumero);
				posTokens.insert({posiciones[principio], tokenNumero});
				estado = 0;
				i = principio;
				if (principio != 0)
				{
					cadena.erase(cadena.begin() + principio, cadena.begin() + final);
					posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);
					cadena[principio] = ' ';
				}
				else
				{
					cadena.erase(cadena.begin() + principio, cadena.begin() + final);
					posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);
				}
				iEnd = cadena.size();
				continue;
			}

			break;

		default:
			break;
		}

		++i;
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
	case 29:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;

	case 30:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 31:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
	case 32:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
	case 33:
		currentPos = principio + 1;
		currentState = 0;
		break;

	case 34:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back(' ');
		cadenaTokens.push_back(cadena[currentPos]);
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 28:
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

void Tokenizador::updateTokens(short &currentState, const string& cadena, std::string &cadenaTokens, size_t &principio, size_t &final_, int &currentPos) const
{
	switch (currentState)
	{
	case 29:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;

	case 30:
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 31:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back('\n');
		currentState = 0;
	case 32:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
	case 33:
		currentPos = principio + 1;
		currentState = 0;
		break;

	case 34:
		cadenaTokens.push_back('0');
		cadenaTokens.append(std::string(cadena, principio, currentPos - principio - 1));
		cadenaTokens.push_back(' ');
		cadenaTokens.push_back(cadena[currentPos]);
		cadenaTokens.push_back('\n');
		currentState = 0;
		break;
	case 28:

		cadenaTokens.append(std::string(cadena, principio, final_ - principio));
		cadenaTokens.push_back('\n');
		currentState = 0;
		currentPos = final_;
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
void Tokenizador::procesarNumero(std::string &numero) const
{
	auto pos = numero.find_first_of("0123456789", 0);
	if (pos == 0)
		return;
	numero.erase(0, pos - 1);
	numero = (numero[0] == ',') ? '0' + numero : numero.erase(0, 1);
}

void Tokenizador::casoEspecialEmail(std::vector<char> &cadena, std::vector<unsigned int> &posiciones, std::map<unsigned int, string> &posTokens) const
{
	unsigned int iEnd = cadena.size();
	unsigned int principio = 0;
	unsigned int i = 0;
	unsigned int final = 0;
	unsigned char conjunto = 0;
	unsigned char estado = 0;

	while (i < cadena.size())
	{
		if (cadena[i] == '@')
			if (this->delimiters.find('.') != string::npos)
				conjunto = 1;
			else
				conjunto = 2;
		else if (this->delimiters.find('.') != string::npos)
			conjunto = 3;
		else
			conjunto = 0;

		switch (estado)
		{
		case 3:
			estado = TP_EMAIL[3][conjunto];

			if (estado == 4)
			{
				estado = 0;
				final = i;
				posTokens.insert({posiciones[principio], std::string(cadena.begin() + principio, cadena.begin() + final)});
				i = principio;
				if (principio != 0)
				{
					cadena.erase(cadena.begin() + principio, cadena.begin() + final);
					posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);
					cadena[principio] = ' ';
				}
				else
				{
					cadena.erase(cadena.begin() + principio, cadena.begin() + final);
					posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);
				}
				iEnd = cadena.size();
				continue;
			}

			break;
		case 0:
			principio = i;
		default:
			estado = TP_EMAIL[estado][conjunto];
			break;
		}
		++i;
	}
}

void Tokenizador::casoEspecialMultipalabra(std::vector<char> &cadena, std::vector<unsigned int> &posiciones, std::map<unsigned int, string> &posTokens) const
{
	unsigned int iEnd = cadena.size();
	unsigned int principio = 0;
	unsigned int i = 0;
	unsigned int final = 0;
	unsigned char conjunto = 0;
	unsigned char estado = 0;

	while (i < cadena.size())
	{
		if (delimiters.find(cadena[0]) != string::npos)
		{
			cadena.erase(cadena.begin() + 0);
			posiciones.erase(posiciones.begin() + 0);
			--iEnd;
			continue;
		}

		if (cadena[i] == '-')
			conjunto = 1;
		else if (delimiters.find(cadena[i]) != string::npos)
			conjunto = 2;
		else
			conjunto = 0;

		switch (estado)
		{
		case 3:
		case 4:
			final = (estado == 3) ? i : i - 1;
			estado = TP_MULTIPALABRA[estado][conjunto];
			if (estado == 5)
			{
				estado = 0;
				posTokens.insert({posiciones[principio], std::string(cadena.begin() + principio, cadena.begin() + final)});
				cadena.erase(cadena.begin() + principio, cadena.begin() + final);
				posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);

				if (principio != 0)
					cadena[principio] = ' ';

				i = principio;
				iEnd = cadena.size();
				continue;
			}
			break;

		default:
			if (estado == 0)
				principio = i;
			estado = TP_MULTIPALABRA[estado][conjunto];
			break;
		}

		++i;
	}

	// Ha terminado de recorrer la cadena. Ultima iteracion.
	switch (estado)
	{
	case 3:
	case 4:
		final = (estado == 3) ? iEnd : iEnd - 1;
		posTokens.insert({posiciones[principio], std::string(cadena.begin() + principio, cadena.begin() + final)});
		cadena.erase(cadena.begin() + principio, cadena.begin() + final);
		posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);
		if (principio != 0)
			cadena[principio] = ' ';
		break;
	default:
		break;
	}
}

// TODO: Modificar el grafo para que no detecte multiples letras como acronimo
void Tokenizador::casoEspecialAcronimo(std::vector<char> &cadena, std::vector<unsigned int> &posiciones, std::map<unsigned int, string> &posTokens) const
{
	unsigned int iEnd = cadena.size();
	unsigned int principio = 0;
	unsigned int i = 0;
	unsigned int final = 0;
	unsigned char conjunto = 0;
	unsigned char estado = 0;

	while (i < iEnd)
	{
		if (delimiters.find(cadena[0]) != string::npos)
		{
			cadena.erase(cadena.begin() + 0);
			posiciones.erase(posiciones.begin() + 0);
			--iEnd;
			continue;
		}

		if (cadena[i] == '.')
			conjunto = 1;
		else if (delimiters.find(cadena[i]) != string::npos)
			conjunto = 2;
		else
			conjunto = 0;

		switch (estado)
		{

		case 3:
		case 4:
			// TODO: Comprobar si es mejor tener dos if y no tener que hacer esta asignacioon todo el ratos.
			final = (estado == 3) ? i : i - 1;
			estado = TP_ACRONIMO[estado][conjunto];

			if (estado == 5)
			{
				estado = 0;
				string borrar(cadena.begin() + principio, cadena.begin() + final);
				posTokens.insert({posiciones[principio], std::string(cadena.begin() + principio, cadena.begin() + final)});
				i = principio;
				cadena[principio] = ' ';
				cadena.erase(cadena.begin() + principio + 1, cadena.begin() + final);
				posiciones.erase(posiciones.begin() + principio + 1, posiciones.begin() + final);
				iEnd = cadena.size();

				continue;
			}
			break;

		default:
			estado = TP_ACRONIMO[estado][conjunto];
			if (estado == 0)
			{
				principio = i;
				++estado;
			}
			break;
		}

		++i;
	}

	// Ha terminado de recorrer la cadena. Ultima iteracion.
	if (estado != 3 && estado != 4)
		return;
	else if (estado == 3)
		final = iEnd;
	else
		final = iEnd - 1;

	posTokens.insert({posiciones[principio], std::string(cadena.begin() + principio, cadena.begin() + final)});
	cadena.erase(cadena.begin() + principio, cadena.begin() + final);
	posiciones.erase(posiciones.begin() + principio, posiciones.begin() + final);
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
	string delimitadoresUnicos = nuevoDelimiters + " \n";
	eliminarCaracteresRepetidos(delimitadoresUnicos);

	// this->delimiters.mapDelimiters = unordered_set<char>(begin(nuevoDelimiters), end(nuevoDelimiters));
	// this->delimiters.mapDelimiters.insert(' ');
	// this->delimiters.mapDelimiters.insert('\n');

	// this->delimiters.delimitadoresOrdenados = delimitadoresUnicos;
	this->delimiters = delimitadoresUnicos;
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
		// Print current character
		/*if (this->delimiters.delimitadoresOrdenados.find(*it) != string::npos)
			this->delimiters.mapDelimiters.insert(*it);
		this->delimiters.delimitadoresOrdenados += *it;*/
		if (this->delimiters.find(*it) == string::npos)
			this->delimiters += *it;
	}
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
void Tokenizador::eliminarCaracteresRepetidos(string &cadena)
{
	string res = "";

	for (auto it = cadena.begin(); it != cadena.end(); ++it)
	{
		if (res.find(*it) == string::npos)
			res += *it;
	}

	cadena = res;
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
	if (caracter >= 0x41 && caracter <= 0x5a)
	{
		caracter += 32;
	}
	else if ((caracter >= 0xc0 && caracter <= 0xc5) || (caracter >= 0xe0 && caracter <= 0xe5)) // A
	{
		caracter = 0x61;
	}
	else if ((caracter >= 0xc8 && caracter <= 0xcb) || (caracter >= 0xe8 && caracter <= 0xeb)) // E
	{
		caracter = 0x65;
	}
	else if ((caracter >= 0xcc && caracter <= 0xcf) || (caracter >= 0xec && caracter <= 0xef)) // I
	{
		caracter = 0x69;
	}
	else if ((caracter >= 0xd2 && caracter <= 0xd6) || (caracter >= 0xf2 && caracter <= 0xf6)) // O
	{
		caracter = 0x6f;
	}
	else if ((caracter >= 0xd9 && caracter <= 0xdc) || (caracter >= 0xf9 && caracter <= 0xfc)) // U
	{
		caracter = 0x6f;
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

	if (this->delimiters.find(caracter) != string::npos)
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
		case '/':
		case '?':
		case '&':
		case '=':
		case '#':
			return 6;

		default:
			return 7;
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
			return 8;
		case 'h':
			return 9;
		case 'f':
			return 10;
		default:
			return 11;
		}
	}
}
