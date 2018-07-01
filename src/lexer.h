#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdio>
using namespace std;

enum Tag { EXPRESSION = 256, TYPE, NUM, ID};

struct Token
{
	int tag;
	Token() : tag(0){}
	Token(int t) : tag(t) {}
};

struct Num : public Token
{
	float value;
	Num() : Token(Tag::NUM), value(0) {}
	Num(float v) : Token(Tag::NUM), value(v) {}
};

struct Id : public Token
{
	string name;
	Id(): Token(Tag::ID) {}
	Id(int t, string s) : Token(t), name(s) {}
};

class Lexer
{
private:
	int  line = 1;
	int col = 1;
	int lastCol = 1;
	char peek = ' ';

	struct {
		Token t;
		Num n;
		Id i;
	}
	token;
	
	ifstream fileExp;
	unordered_map<string, Id> id_table;

	void Reserve(Id w);
	void Clear();  				// limpar tabulações, espaços e novas linhas;
	void CleanComm();			// limpar comentários

public:
	Lexer();
	Token* Scan();
	void Start(string fileName);	// inicializador
	void Stop(); 					// fecha o arquivo
	int getLine();					// retorna linha atual
	int getCol();					// retorna coluna atual
	int getLastCol();					// retorna ultima coluna

	string dumpFile();				// retorna todo conteúdo do arquivo
};