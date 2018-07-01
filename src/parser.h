#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <map>

#include "lexer.h"
#include "env.h"


using namespace std;


class Parser
{
private:

	
	// char lookahead;
	Token * lookahead;
	Symbol * found;
	Lexer analex;
	// Env rootScope;
	Env scope;

	bool init = true;

	void Program();
	void Block();
	void Decls();
	void Stmts();
	void Decl();
	void Stmt();
	void Expr();

	void Term();
	void Factor();

	void Oper1();
	void Oper2();

	void Match(char t);

public:
	Parser();
	void Start(string args1);
};