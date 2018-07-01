#include <locale.h>
#include <time.h>
#include "parser.h"

#define EXT_FILE ".exp"

using namespace std;

void showUsage(string name, bool flag);
void Start(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); // só funciona aqui
	
    Start(argc, argv); // trabalhando parâmetros

    Parser t800; // declaração do parser

    time_t now = time(NULL);
	try
	{
		t800.Start(argv[1]);
		
	}
	catch (string error)
	{
		cout << endl <<  error << endl;
	}
    // benchmark
    cout << "\n[Finalizado em "<< difftime(time(NULL),now) << "s]\n";

    return 0;
}
void Start(int argc, char* argv[]) {	

 	// Checando o número de parâmetros
    if (argc == 1) {
        // Conte ao usuário como rodar o programa
        showUsage(argv[0], true);
        exit(EXIT_FAILURE);
    }

    if (argc > 1) {
        string args1 = argv[1]; 
        
        if ((args1 == "--help") || (args1 == "-h")){ // se for help
            // Conte ao usuário como rodar o programa
            showUsage(argv[0], false);
            exit(EXIT_SUCCESS);
        }

        string ext = EXT_FILE;
        // testemos que o argumento provem de uma arquivo de extensão válida (.exp)

        if ((args1.size() <= 4) || (args1.substr(args1.size()-ext.size(),ext.size()) != ext)) {
             // Conte ao usuário como rodar o programa
            cerr << "\n\t\tNome de arquivo inválido!\n\n";
            showUsage(argv[0], true);
            exit(EXIT_FAILURE);
        } 
        
        // cout << "\n\tNome de arquivo válido!\n\n";
    }
}

void showUsage(string name, bool flag) // função para mostrar uso
{
    string usage =  "Uso: " + name + " [ <opções> | SOURCE.exp ]\nOpções:\n\t-h,--help\t\tMostra esta mensagem de ajuda\n\n";

    if (flag) {
        cerr << usage;
    } else {
        cout << usage;
    }
}