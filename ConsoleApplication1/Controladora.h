#pragma once
#include <iostream>
#include "Dependencias.h"
#include "conio.h"
#include "Lista1.h"
#include "Usuario.h"
#include "Canciones.h"

class Controladora
{
private:
	std::vector<Usuario> listaUsuarios; 
public:
	Controladora() {};
	~Controladora() {};

	
    void menuRegistrarUsuario() {};
    void menuEliminarUsuario() {};
    void menuIniciarSesion() {
        std::string idBuscado, passIngresada;
        BorrarPantallaEscribible();
     
        gotoxy(13, 37); std::cout << "Ingrese ID: ";
        std::cin >> idBuscado;

        bool encontrado = false;

        for (Usuario& usuarioActual : listaUsuarios) {

            if (usuarioActual.getId() == idBuscado) {
                encontrado = true;
                gotoxy(14, 37); std::cout << "Usuario encontrado. Ingrese contrasena: ";
                std::cin >> passIngresada;

                if (usuarioActual.getContrasena() == passIngresada) {
                    gotoxy(16, 37); std::cout << "¡Bienvenido, " << usuarioActual.getNombreUsuario() << "!";
                }
                else {
                    gotoxy(16, 37); std::cout << "Contrasena incorrecta.";
                }
                break; 
            }
        }

        if (!encontrado) {
            gotoxy(16, 37); std::cout << "El usuario no existe.";
        }
    }


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
            else if (tecla == 13) { 
                switch (indiceFondoIniciarSesion) {
                case 1: menuIniciarSesion(); _getch(); break;
                case 2: menuRegistrarUsuario(); _getch(); break;
                case 3: menuEliminarUsuario(); _getch(); break;
                }
            }
            BorrarPantallaEscribible();
        }
    }

};

