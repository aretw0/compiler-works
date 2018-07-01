#include "env.h"

Env::Env(){
	prev = NULL;
}
Env::Env(Env * p){
	prev = p;
}

void Env::put(string s, Symbol sym) { 
	scope_table[s] = sym;
}

Symbol * Env::get(string s) {
	for (Env * e = this; e != NULL; e = e->prev) {
		auto pos = e->scope_table.find(s);

		if (pos != e->scope_table.end()) {
			found = pos->second;

			return &found;
		}
	}
	return NULL;
}  



/*int main(int argc, char* argv[]) {

}*/