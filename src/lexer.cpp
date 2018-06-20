#include "lexer.h"
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;
using std::stringstream;

void Lexer::Reserve(Id w)
{
	id_table[w.name] = w;
}

Lexer::Lexer()
{
	Reserve(Id{ Tag::TRUE, "true" });
	Reserve(Id{ Tag::FALSE, "false" });
}

Token Lexer::Scan()
{
	// salta espaços em branco, tabulações e novas linhas
	while (isspace(peek))
	{
		if (peek == '\n')
			line += 1;
		// peek = fileExp.get();
		fileExp >> peek;
	}

	// retorna números
	if (isdigit(peek))
	{
		int v = 0;
		
		do 
		{
			// converte 'n' para o dígito numérico n
			int n = peek - '0';
			v = 10 * v + n;
			// peek = fileExp.get();
			fileExp >> peek;
		} 
		while (isdigit(peek));

		cout << "<NUM," <<  v <<"> ";
		return Num{v};
	}

	// retorna palavras-chave e identificadores
	if (isalpha(peek))
	{
		if (peek=='/') {
			// peek = fileExp.get();
			fileExp >> peek;
			if (peek == '/') {

			}
		}
		stringstream ss;

		do 
		{
			
			ss << peek;
			peek = fileExp.get();
		} 
		while (isalpha(peek));

		string s = ss.str();
		auto pos = id_table.find(s);

		if (pos != id_table.end())
		{
			switch (pos->second.tag)
			{
			case TRUE: cout << "<" << "TRUE" << "," << pos->second.name << "> "; break;
			case FALSE: cout << "<" << "FALSE" << "," << pos->second.name << "> "; break;
			default: cout << "<" << "ID" << "," << pos->second.name << "> "; break;
			}
			
			return pos->second;
		}

		Id w{Tag::ID, s};
		id_table[s] = w;
		cout << "<" << "ID" << "," << w.name << "> ";
		return w;
	}

	// retorna operadores (e caracteres não alphanuméricos isolados)
	Token t{ peek };
	peek = ' ';
	cout << "<" << char(t.tag) << "> ";
	return t;
}

void Lexer::Start(string fileName)
{
	fileExp.open(fileName);

	if (!fileExp.is_open()) {
        cerr << "\n\t\tArquivo inválido!\n\n";           
    } else {
		// while (fileExp >> peek)
		while (peek != '/n')
			Scan();
    }

	fileExp.close();
}


