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
	char peek = ' ';

	struct {
		Token t;
		Num n;
		Id i;
	}
	token;

	// Token tkLex;
	
	ifstream fileExp;

	unordered_map<string, Id> id_table;
	void Reserve(Id w);

public:
	Lexer();
	Token* Scan();
	// Token Scan();
	void Start(string fileName);
	void Stop();
	void Clear();
	void CleanComm();
	int getLine();
	// char getPeek();
	string getStep();

	char getNext(char before);
	void ignoreLineComm(char before);
	void ignoreBlockComm(char before);
	void verifyEnd(char before);

	string dumpFile();
};