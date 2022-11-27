# Tokenizer
A very fast and low memory usage C++ tokenizer that breaks an input string into a list of tokens looking at tabs, spaces, new lines, and detects special tokens like numbers, prces, personal noms, emails, lexemes, etc. It allows to specify delimeters, detect special cases and change to lowercase the tokens. 
It uses an automaton to detect the special tokens.

Note:
The automaton is design to detect this specifics examples. To detect more cases not contemplated on this version, modify the automaton matriz: `const unsigned char Tokenizador::TP_AUTOMATA[][]`

## How to use it
There are test cases on `src/`. Here is an example:

```C++
#include <iostream> 
#include <string>
#include <list> 
#include "tokenizador.h"

using namespace std;

void imprimirListaSTL(const list<string>& cadena)
{
        list<string>::const_iterator itCadena;
        for(itCadena=cadena.begin();itCadena!=cadena.end();itCadena++)
        {
                cout << (*itCadena) << ", ";
        }
        cout << endl;
}

int main(void)
{
    bool spcialCases = true, lowercaseTokens = true;

    list<string> lt1;

    // Delimeters: []# 
    // Detect special cases: True
    // Output in lowercase: True
    Tokenizador a("[]# ", spcialCases, lowercaseTokens);
    a.Tokenizar("pal1 cat@iuii.ua.es@cd p1 p2", tokens);
    imprimirListaSTL(tokens);
    
    // Output
    //[pal1, cat, iuii.ua.es, cd, p1, p2]

    
}
```


## Whay I Learned
- How to develop automatons for pattern recognition.
- How to optimize C++ memory.
- How to optimize C++ execution times.
- Design algorithms.
- Minimize automatons nodes.
