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

	Token * lookahead;
	Lexer analex;
	Symbol * found;
	Env * scope;

	bool init = true;	// para fins de inicialização


						
						
						
						
						
						
						






	void Program();	//	->	expression block
	void Block();	//	->	{ decls stmts }
	void Decls();	//	->	decl decls
					//	|	ε
	void Decl();	//	->	type id;
	void Stmts();	//	->	stmt stmts
					//	|	ε
	void Stmt();	//	->	block
					//	|	expr;
	void Expr();	//	->	term oper1
	void Oper1();	//	->	+ term oper1
					//	|	– term oper1
					//	|	ε				
	void Term();	//	->	factor oper2
	void Oper2();	//	->	* factor oper2
					//	|	/ factor oper2
					//	|	ε
	void Factor();	//	->	(expr)
					//	|	num
					//	|	id
	
	void Match(char t);
	void Match(char t, int line);

public:
	Parser();
	void Start(string args1);
};