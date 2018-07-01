#include <string>
#include <unordered_map>

using namespace std;

struct Symbol{
    string name;
    string classtype;
    Symbol() {}
    Symbol(string n, string c): name(n), classtype(c) {}
};


class Env 
{
private: 
    unordered_map<string,Symbol> scope_table;
    Env * prev;
    Symbol found;
public:
   Env(Env * p);
   Env();
   void put(string s, Symbol sym);
   Symbol * get(string s);
};