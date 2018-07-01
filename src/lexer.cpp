#include "lexer.h"
#include <iostream>
#include <sstream>

void Lexer::Reserve(Id w)
{
	id_table[w.name] = w;
}
int Lexer::getLine() {
	return line;
}

string Lexer::getStep(){
	return line + " com " + peek;
}

char Lexer::getNext(char before) {
	char next = fileExp.get();
	verifyEnd(before);
	return next;
}
void Lexer::ignoreLineComm(char before) {
	// cout << fileExp.getLine();
	fileExp.ignore(256,'\n');
	// verifyEnd(before);
	++line;
}

void Lexer::ignoreBlockComm(char before) {
	char next;
	while (true) {
		next = fileExp.get();
		if (next == '*') {
			next = fileExp.peek();
			if (next == '/'){
				next = fileExp.get();
				break;
			}
		} else if (next == '\n') {
			++line;
		} else if (fileExp.eof()) {
			break;
		}
	}
}

void Lexer::verifyEnd(char before) {
	if (fileExp.eof()) {
		Stop();
		throw "Erro de sintaxe: Fim do arquivo em linha: " + to_string(line) + " com " + before;
	}
}

Lexer::Lexer()
{
	Reserve(Id{ Tag::EXPRESSION, "expression" });
	Reserve(Id{ Tag::TYPE, "int" });
	Reserve(Id{ Tag::TYPE, "float" });
}

void Lexer::Clear() {
	// salta espa�os em branco, tabula��es e novas linhas
	while (isspace(peek))
	{
		if (peek == '\n')
			++line;
		peek = fileExp.get();
	}
}

void Lexer::CleanComm() {
	while (peek == '/') {
		char next = fileExp.peek();
		if (next == '/') {
			// cout << "\nIgnorando comentario de linha!\n";
			ignoreLineComm(peek);
			peek = fileExp.get();
			Clear();
		} else if (next == '*') {
			// cout << "\nIgnorando comentario de bloco!\n";
			ignoreBlockComm(peek);
			peek = fileExp.get();
			Clear();
		} else {
			break;
		}
	}
}

Token * Lexer::Scan()
{
	Clear();
	CleanComm();

	// retorna n�meros
	if (isdigit(peek))
	{	
		stringstream ss;
		bool doFloat = false;
		do 
		{
			// captura um string num�rica
			ss << peek;
			
			peek = fileExp.get();

			if ((peek == '.') && (isdigit(fileExp.peek())) && (!doFloat)) {
				doFloat = true;
				ss << peek;
				peek = fileExp.get();
			}
		} 
		while (isdigit(peek));

		string s = ss.str();

		// cout << "\nDigito " << s << '\n';

		Num m{stof(s)}; // utiliza stof para converter para float
		token.n = m;

		return &token.n;
	}

	// retorna palavras-chave e identificadores
	if (isalpha(peek))
	{
		stringstream ss;

		do 
		{
			ss << peek;
			peek = fileExp.get();
		
		} 
		while (isalpha(peek));
		

		string s = ss.str();

		// cout << "\nAlpha " << s << endl;

		auto pos = id_table.find(s);

		if (pos != id_table.end())
		{
			/*switch (pos->second.tag)
			{
				case EXPRESSION: cout << "<" << "EXPRESSION" << "," << pos->second.name << "> "; 
					break;
				case TYPE: cout << "<" << "TYPE" << "," << pos->second.name << "> ";
					break;
				case NUM: cout << "<" << "NUM" << "," << pos->second.name << "> ";
					break;
				default: cout << "<" << "ID" << "," << pos->second.name << "> ";
					break;
			// }*/

			token.i = pos->second;
			
		} else {
			Id w{Tag::ID, s};
			id_table[s] = w;
			token.i = w;
		}
		return &token.i;
		// tkLex = w;
		// cout << "<" << "ID" << "," << w.name << "> ";
		// return &tkLex;
	}

	// retorna operadores (e caracteres n�o alphanum�ricos isolados)
	// tkLex{ peek };
	// peek = ' ';
	// cout << "<" << char(t.tag) << "> ";
	// return &tkLex;
	// cout << "\nOutros: " << peek << endl;
	Token t{ peek };
	token.t = t;
	peek = ' ';
	// cout << "<" << char(t.tag) << "> ";
	return &token.t;
}

void Lexer::Start(string fileName)
{
	// fileExp = file;

	/*if (!fileExp.is_open()) {
        cerr << "\n\t\tArquivo inv�lido!\n\n";           
    } else {
		// while (fileExp >> peek)
		while (peek != '/n')
			Scan();
    }*/

	// fileExp.close();

	 fileExp.open(fileName);

    if (!fileExp.is_open()) {
        // exit(EXIT_FAILURE);
        throw "Arquivo " + fileName + " inexistente";
        // return 1;
    }
}

void Lexer::Stop() {
	fileExp.close();
}

string Lexer::dumpFile() {
	cout << "dumpFile\n";
	while (!fileExp.eof()) {
		char show = fileExp.get();
		if (!fileExp.eof())
			cout << show;
	}
}