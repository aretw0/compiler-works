#include <locale.h>
#include "tradutor.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Portuguese");	

	Tradutor t800(argc, argv);

    return 0;
}