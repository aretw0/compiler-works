#include <fstream>
#include <locale.h>
#include <iostream>
// #include "tradutor.h"

using namespace std;



int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Portuguese");	

	/*for (int i = 0; i <= argc; ++i) {
		cout << argv[i] << endl;
	}*/

 	// Checando o número de parâmetros
    if (argc < 1) {
        // Conte ao usuário como rodar o programa
        cerr << "Uso: " << argv[0] << " INPUTFILE.exp" << endl;
      
        return 1;
    }
    // Print the user's name:
    cout << argv[0] << "diz olá, " << argv[1] << "!" << endl;
    return 0;
}