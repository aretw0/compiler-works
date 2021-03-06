#include "parser.h"

Parser::Parser(){}

void Parser::Start(string args1) {
        analex.Start(args1);
		lookahead = analex.Scan();
		Program();
		analex.Stop();
}

void Parser::Match(char t)
{
	if (t == lookahead->tag)
		lookahead = analex.Scan();
	else
		throw "Erro de sintaxe na linha: " + to_string(analex.getLine()) + "\nEsperava-se '"+t+"'\n";
}
void Parser::Match(char t,int line)
{
	if (t == lookahead->tag)
		lookahead = analex.Scan();
	else
		throw "Erro de sintaxe na linha: " + to_string(line) + "\nEsperava-se '"+t+"'\n";
}

void Parser::Program() {
	if (lookahead->tag == EXPRESSION) { // Para Come�ar certo
		lookahead = analex.Scan(); // inicia arquivo a dentro
		scope = new Env();
		Block(); // decompondo para o proximo	
	} else {
		throw "Erro de sintaxe na linha: " + to_string(analex.getLine()) + "\nDeve-se iniciar com 'expression'\n";
	}
}
void Parser::Block() {
	Match('{'); // Para come�ar certo
	// reservar novo escopo
	Env * saved = scope;

	if (init) {
		init = false;
	} else {
		scope = new Env(scope);
	}

	Decls(); // decompondo para o proximo	
	Stmts(); // decompondo para o proximo	

	// voltar pra antigo escopo
	scope = saved;

	Match('}'); // Para começar certo
	// voltar para o escopo anterior
}

void Parser::Decls() {
	while (true) {
		if (lookahead->tag == TYPE) {
			Decl();
		} else {
			break;
		}
	}
}

void Parser::Decl(){
	Id type = *(Id*)lookahead;
	int actuaLine = analex.getLine();
	lookahead = analex.Scan();
	if (lookahead->tag == ID){
		Id id = *(Id*)lookahead;
		actuaLine = analex.getLine();
		lookahead = analex.Scan();
		Match(';',actuaLine);

		// Eis o momento de carregar as vari�veis na tabela de simbolos

		Symbol s{id.name,type.name};

		if(!scope->search(id.name)) {
			scope->put(id.name,s);
		} else {
			throw "Erro de sintaxe na linha: " + to_string(actuaLine) + "\nDeclaração '"+id.name+"' duplicada no escopo\n";			
		}

	} else {
		throw "Erro de sintaxe na linha: " + to_string(actuaLine) + "\nDeclaração '"+type.name+"' incompleta\n";
	}
}

void Parser::Stmts(){
	bool run = true;
	while (run) {
		switch (lookahead->tag) {
			case '{': // casos de Stmt
			case '(':
			case ID:
			case NUM:
				Stmt(); // decompondo para o proximo
				break;
			default:
				run = false;
				break;
		}
	}
}

void Parser::Stmt(){
	if ('{' == lookahead->tag) {
		Block(); // decompondo para o proximo
	} else {
		int lastLine = analex.getLine();
		Expr(); // decompondo para o proximo
		Match(';',lastLine); // terminando certo
		cout << endl;
	}
}

void Parser::Expr()
{
	// expr -> term oper1
	Term(); // decompondo para o proximo	
	Oper1(); // decompondo para o proximo
}

void Parser::Term()
{
	// term - > factor oper2
	Factor(); // decompondo para o proximo
	Oper2(); // decompondo para o proximo	
}

void Parser::Oper1() {

	// oper1 -> term oper1
	while (true) {
		if (lookahead->tag == '+') {
			Match('+');
			Term();
			cout << '+';
		
		} else if (lookahead->tag == '-') {
			Match('-');
			Term();
			cout << '-';
		} else return;
	}	
}

void Parser::Oper2() {
	// oper2 -> factor oper2
	while (true) {
		if (lookahead->tag == '*') {
			Match('*');
			Factor();
			cout << '*';
		
		} else if (lookahead->tag == '/') {
			Match('/');
			Factor();
			cout << '/';
		} else return;
	}
}

void Parser::Factor() {
	switch (lookahead->tag) {
		case ID:
			{
				// procurar nos escopos informaçõees
				Id i = *(Id*)lookahead;
				// ver se tem operador e o mostrar-lo
				found = scope->get(i.name);
				if (!found) { // conclusao que foi declarada
					throw "Erro de sintaxe na linha: "+ to_string(analex.getLine()) + "\n" + i.name + " foi declarada?\n";
				} else {
					cout << '(' << found->classtype << ':' << found->name << ")";
				}
				lookahead = analex.Scan();	
				break;
			}
		case NUM:
			{
				// informações
				Num n = *(Num*)lookahead;
				cout << '(' << n.value << ')';
				// ver se tem operador para cuspir e o fazer
				lookahead = analex.Scan();	
				break;	
			}
		default:
			Match('(');
			Expr();
			Match(')');
			break;
	}
}