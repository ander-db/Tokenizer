#include "tokenizador.h"

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
	eliminarCaracteresRepetidos(stringDelimitadoresUnicos);
	
	this->delimiters = delimitadoresPalabra;

	//this->delimiters.mapDelimiters = unordered_set<char>(begin(delimitadoresPalabra), end(delimitadoresPalabra));
	//this->delimiters.mapDelimiters.insert(' ');
	//this->delimiters.mapDelimiters.insert('\n');

	//this->delimiters.delimitadoresOrdenados = stringDelimitadoresUnicos;

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
	//this->delimiters = DEFAULT_STRUCT_DELIMITADORES;
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
	//this->delimiters.delimitadoresOrdenados.clear();
	//this->delimiters.delimitadoresOrdenados = "";
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

	// TODO: Casos especiales
	/*string::size_type lastPos = str.find_first_not_of(delimiters.delimitadoresOrdenados, 0);
	string::size_type pos = str.find_first_of(delimiters.delimitadoresOrdenados, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(this->delimiters.delimitadoresOrdenados, pos);
		pos = str.find_first_of(this->delimiters.delimitadoresOrdenados, lastPos);
	}*/
	//tokens = std::list<string>(aux.begin(), aux.end());
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(this->delimiters, pos);
		pos = str.find_first_of(this->delimiters, lastPos);
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

		// ** Mas memoria. Mas rapido. 4400kb - 3 segs
		/**
		ifstream bigFile("mybigfile.dat");
		constexpr size_t bufferSize = 1024 * 1024;
		unique_ptr<char[]> buffer(new char[bufferSize]);
		while (bigFile)
		{
			bigFile.read(buffer.get(), bufferSize);
			Tokenizar(cadena, tokens); //
			// process data in buffer

		}*/
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
				Tokenizar(cadena);
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

	//this->delimiters.mapDelimiters = unordered_set<char>(begin(nuevoDelimiters), end(nuevoDelimiters));
	//this->delimiters.mapDelimiters.insert(' ');
	//this->delimiters.mapDelimiters.insert('\n');

	//this->delimiters.delimitadoresOrdenados = delimitadoresUnicos;
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
	//return this->delimiters.delimitadoresOrdenados;
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
