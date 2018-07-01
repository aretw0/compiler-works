#include "lexer.h"
#include <iostream>
#include <sstream>

Lexer::Lexer()
{
	Reserve(Id{ Tag::EXPRESSION, "expression" });
	Reserve(Id{ Tag::TYPE, "int" });
	Reserve(Id{ Tag::TYPE, "float" });
}
int Lexer::getLine() {
	return line;
}
int Lexer::getCol() {
	return col;
}
int Lexer::getLastCol(){
	return lastCol;
}

void Lexer::Reserve(Id w)
{
	id_table[w.name] = w;
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
		++col;
		int lastLine = line;
		char next = fileExp.peek();
		if (next == '/') {
			// Ignorando comentario de linha 
			fileExp.ignore(256,'\n');
			++line;
			lastCol = col;
			col = 1;
			peek = ' ';
			Clear();
		} else if (next == '*') {
			// Ignorando comentario de bloco
			char temp;
			while (true) {
				temp = fileExp.get();
				++col;
				if (temp == '*') {
					temp = fileExp.peek();
					if (temp == '/'){
						temp = fileExp.get();
						++col;
						break;
					}
				} else if (temp == '\n') {
					++line;
					lastCol = col;
					col = 1;
				} else if (fileExp.eof()) {
					throw "Erro de sintaxe na linha: " + to_string(lastLine)+"\nBloco de comentário aberto";
				}
			}
			peek = ' ';
			Clear();
		} else {
			break;
		}
	}
}

void Lexer::Start(string fileName)
{
	fileExp.open(fileName);
    if (!fileExp.is_open()) {
        throw "Arquivo " + fileName + " inexistente";
    }
}

void Lexer::Stop() {
	fileExp.close();
}

Token * Lexer::Scan()
{
	Clear();
	CleanComm();

	// retorna números
	if (isdigit(peek))
	{	
		stringstream ss;
		bool doFloat = false;
		do 
		{
			// captura um string numérica
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

		auto pos = id_table.find(s);

		if (pos != id_table.end())
		{
			token.i = pos->second;
			
		} else {
			Id w{Tag::ID, s};
			id_table[s] = w;
			token.i = w;
		}
		return &token.i;
	}

	// retorna operadores (e caracteres não alphanuméricos isolados)
	Token t{ peek };
	token.t = t;
	peek = ' ';
	return &token.t;
}

string Lexer::dumpFile() {
	cout << "dumpFile\n";
	while (!fileExp.eof()) {
		char show = fileExp.get();
		if (!fileExp.eof())
			cout << show;
	}
}