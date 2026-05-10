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

    void menuRegistrarUsuario() {
        std::string nId, nNombre, nCorreo, nPass;
        BorrarPantallaEscribible(); 
        std::cout << "\033[38;2;146;208;80m"; //verde spotyfy
        gotoxy(13, 32); std::cout << "--- REGISTRO DE USUARIO ---";
        gotoxy(14, 32); std::cout << "Ingrese ID: "; std::cin >> nId;

        // Verificamos si el ID ya existe antes de seguir
        bool existe = false;
        for (Usuario& u : listaUsuarios) {
            if (u.getId() == nId) {
                existe = true;
                break;
            }
        }

        if (existe) {
            gotoxy(16, 37); std::cout << "Error: Ya existe un usuario con el ID " << nId;
        }
        else {
            // Si no existe, pedimos el resto de datos
            gotoxy(15, 32); std::cout << "Ingrese Nombre: "; std::cin >> nNombre;
            gotoxy(16, 32); std::cout << "Ingrese Correo: "; std::cin >> nCorreo;
            gotoxy(17, 32); std::cout << "Ingrese Contrasena: "; std::cin >> nPass;

            // Creamos el usuario y lo metemos al vector
            Usuario nuevoUsuario(nId, nNombre, nCorreo, nPass);
            listaUsuarios.push_back(nuevoUsuario);

            gotoxy(19, 32); std::cout << "Usuario registrado con exito!";
        }
        std::cout << "\033[0m";
    }

    void menuEliminarUsuario() {
        std::string idEliminar;
        BorrarPantallaEscribible();
        std::cout << "\033[38;2;146;208;80m"; //verde spotyfy

        gotoxy(13, 34); std::cout << "--- ELIMINAR USUARIO ---";
        gotoxy(14, 34); std::cout << "Ingrese ID a eliminar: ";
        std::cin >> idEliminar;

        bool encontrado = false;

        // Recorremos el vector buscando la posicion (i)
        for (size_t i = 0; i < listaUsuarios.size(); i++) {
            if (listaUsuarios[i].getId() == idEliminar) {
                // Borramos el elemento en la posicion listaUsuarios.begin() + i
                listaUsuarios.erase(listaUsuarios.begin() + i);
                encontrado = true;

                gotoxy(16, 34); std::cout << "Usuario eliminado correctamente.";
                break;
            }
        }

        if (!encontrado) {
            gotoxy(16, 34); std::cout << "Error: No se encontro ningun usuario con ese ID.";
        }
        std::cout << "\033[0m";

    }

    void menuIniciarSesion() {
        std::string idBuscado, passIngresada;
        BorrarPantallaEscribible();
        std::cout << "\033[38;2;146;208;80m"; //verde spotyfy

        gotoxy(13, 37); std::cout << "Ingrese ID: ";
        std::cin >> idBuscado;

        bool encontrado = false;

        for (Usuario& usuarioActual : listaUsuarios) {

            if (usuarioActual.getId() == idBuscado) {
                encontrado = true;
                gotoxy(14, 37); std::cout << "Usuario encontrado";
                gotoxy(15, 37); std::cout << "Ingrese contrasena: ";
                gotoxy(16, 37);
                std::cin >> passIngresada;

                if (usuarioActual.getContrasena() == passIngresada) { //aca adentro entraremos a otra parte del code con weas como las listas de usuario y cosas asi como para registrar cosas segun el usuario xd
                    gotoxy(17, 37); std::cout << "Bienvenido, " << usuarioActual.getNombreUsuario() << "!";
                }
                else {
                    gotoxy(17, 37); std::cout << "Contrasena incorrecta.";
                }
                break; 
            }
        }

        if (!encontrado) {
            gotoxy(16, 37); std::cout << "El usuario no existe.";
        }
        std::cout << "\033[0m";

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

