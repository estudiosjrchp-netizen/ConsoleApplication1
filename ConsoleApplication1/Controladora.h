#pragma once
#include <iostream>
#include "Dependencias.h"
#include "conio.h"

class Controladora
{
private:

public:
	Controladora();
	~Controladora();

	void IniciarPrograma() {
		ImprimirMatrizFondo(fondazo);
		int indiceFondoIniciarSesion = 1;
		while (true) {
			IniciarSesionFondo(13, 37, indiceFondoIniciarSesion);
			char tecla = _getch();
			if (tecla == 115 || tecla == 83) {
				if (indiceFondoIniciarSesion < 3) {
					indiceFondoIniciarSesion++;
				}
			}
			else if (tecla == 119 || tecla == 87) {
				if (indiceFondoIniciarSesion > 1) {
					indiceFondoIniciarSesion--;
				}
			}
		}
	}

};

