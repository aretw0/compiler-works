#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

// #include "lexer.h"
// #include "parser.h"

#define EXT_FILE ".exp"

using namespace std;


class Tradutor
{
private:
	// ifstream fileExp;
	// Lexer analex;
	// Parser anasin;	
public:
	Tradutor(int argc, char* argv[]);
	Tradutor();
	void Init(int argc, char* argv[]);
	void Start(ifstream fileExp);
	void showUsage(string name,bool flag);
};