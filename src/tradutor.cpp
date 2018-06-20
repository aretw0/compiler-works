#include "tradutor.h"


void Tradutor::showUsage(string name, bool flag)
{
    string usage =  "Uso: " + name + " [ <opções> | SOURCE.exp ]\nOpções:\n\t-h,--help\t\tMostra esta mensagem de ajuda\n\n";

    if (flag) {
        cerr << usage;
    } else {
        cout << usage;
    }
}

Tradutor::Tradutor() {
    // analexico();
    // analsin();
    // fileExp();
}


Tradutor::Tradutor(int argc, char* argv[]) {
    // analexico();
    // analsin();
    // fileExp();
    Start(argc,argv);
}
void Tradutor::Start(int argc, char* argv[]) {	

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
            cerr << "\n\t\tArquivo inválido!\n\n";
            showUsage(argv[0], true);
            exit(EXIT_FAILURE);
            // return 1;
        }

        // cout << "Nome de arquivo com extensão válida!\n";

        fileExp.open(args1);

        if (!fileExp.is_open()) {
            cerr << "\n\t\tArquivo inválido!\n\n";
            showUsage(argv[0], true);
            exit(EXIT_FAILURE);
            // return 1;
        }

        cout << "\n\t\tArquivo válido!\n\n";

        /*string contentFile = "";
        string contentLine;

        while ( getline (fileExp,contentLine) )
        {
            cout << contentLine << '\n';

            // adiantamos a busca por comentários de uma linha
            size_t found = contentLine.find("//");
            if (found!=string::npos) {
                // retiramos o comentário e passamos o resto se houver algo
                contentLine = contentLine.substr(0,found);

                if (contentLine.size()) {
                    // Ainda há algo antes do comentários
                    contentFile += contentLine + " "; // espaço de segurança
                }
            } else {
                contentFile += contentLine;
            }

            

            // contentFile += contentLine + "\n";
        }
        cout << "\nResultado: \n\n" << contentFile << endl;
        */

        fileExp.close();
    }
}