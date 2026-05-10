#include <iostream>
#include "Dependencias.h"
#include "conio.h"

int main() {
	ocultarCursor();
	ImprimirMatrizFondo(fondazo);
	while (true) {

		IniciarSesionFondo(13, 37);
	}
	_getch();
	return 0;
}