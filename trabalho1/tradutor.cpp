#include <locale.h>
#include <iostream>
#include <fstream>
#include <string>

// #include "tradutor.h"

using namespace std;


static void mostrar_uso(string name)
{
    cerr << "Uso: " << name << " [ <opções> | SOURCE.exp ]" << endl
    << "Opções:\n"
    << "\t-h,--help\t\tMostra esta mensagem de ajuda\n"
    << endl;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Portuguese");	

	/*for (int i = 0; i <= argc; ++i) {
		cout << argv[i] << endl;
	}*/

 	// Checando o número de parâmetros
    if (argc == 1) {
        // Conte ao usuário como rodar o programa
        mostrar_uso(argv[0]);
        return 1;
    }

    if (argc > 1){
        string args1 = argv[1]; 
        if ((args1 == "--help") || (args1 == "-h")){
            // Conte ao usuário como rodar o programa
            mostrar_uso(argv[0]);
            return 0;
        }

        // if (args1 == )
    }
    // Imprimir
    // cout << argv[0] << " diz olá, " << argv[1] << "!" << endl;






    return 0;
}