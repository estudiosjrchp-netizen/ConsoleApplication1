#pragma once
#include <fstream>
#include <iostream>
#include "Dependencias.h"
#include "conio.h"
#include "Lista1.h"
#include "Usuario.h"
#include "Canciones.h"
#include "Pila.h"
#include "Cola.h"

class Controladora
{
private:
    Lista1<Usuario> listaUsuarios;
    std::string nombreArchivoUsuarios = "usuarios.txt";
    Lista1<Cancion> listaCancionesGlobales;
    std::string nombreArchivoCanciones = "canciones.txt";

    Pila<Cancion> historialReproduccion;
    Cola<Cancion> colaReproduccion;

public:
    Controladora() {
        cargarUsuarios();
        cargarCanciones();
    };
    ~Controladora() {};

    void buscarArtistaRecursivo(int indice, std::string artistaBuscado, std::vector<Cancion>& resultados) {
        if (indice >= listaCancionesGlobales.getCantidad()) { return; }
        Nodo<Cancion>* actual = listaCancionesGlobales.getInicio();
        for (int i = 0; i < indice && actual != nullptr; i++) { actual = actual->siguiente; }

        if (actual != nullptr && actual->dato.getAutor() == artistaBuscado) {
            resultados.push_back(actual->dato);
        }
        buscarArtistaRecursivo(indice + 1, artistaBuscado, resultados);
    }

    void cargarCanciones() {
        std::ifstream archivo(nombreArchivoCanciones);
        if (archivo.is_open()) {
            std::string titulo, autor, genero;
            int duracion;
            while (archivo >> titulo >> autor >> genero >> duracion) {
                Cancion c(titulo, autor, genero, duracion);
                listaCancionesGlobales.agregarAlFinal(c);
            }
            archivo.close();
        }
    }

    void menuVerCancionesGlobales() {
        int paginaActual = 0;
        int cancionesPorPagina = 10;

        while (true) {
            BorrarPantallaEscribible();

            int totalCanciones = listaCancionesGlobales.getCantidad();
            int totalPaginas = (totalCanciones + cancionesPorPagina - 1) / cancionesPorPagina;
            if (totalPaginas == 0) totalPaginas = 1;

            std::cout << "\033[38;2;146;208;80m";
            gotoxy(10, 30); std::cout << "--- REPOSITORIO GENERAL (" << paginaActual + 1 << "/" << totalPaginas << ") ---";
            std::cout << "\033[0m";

            int inicioPagina = paginaActual * cancionesPorPagina;
            int finPagina = std::min(inicioPagina + cancionesPorPagina, totalCanciones);

            Nodo<Cancion>* actual = listaCancionesGlobales.getInicio();
            for (int i = 0; i < inicioPagina && actual != nullptr; i++) {
                actual = actual->siguiente;
            }

            for (int i = inicioPagina; i < finPagina && actual != nullptr; i++) {
                gotoxy(12 + (i - inicioPagina), 15);
                std::cout << i + 1 << ". " << actual->dato.getTitulo() << " - "
                    << actual->dato.getAutor() << " (" << actual->dato.getDuracion() << "s)";
                actual = actual->siguiente;
            }

            std::cout << "\033[38;2;255;255;0m";
            gotoxy(23, 15); std::cout << "[A] Atras | [D] Siguiente | [ESC] Salir";
            std::cout << "\033[0m";

            char tecla = _getch();
            if ((tecla == 'a' || tecla == 'A') && paginaActual > 0) {
                paginaActual--;
            }
            else if ((tecla == 'd' || tecla == 'D') && paginaActual < totalPaginas - 1) {
                paginaActual++;
            }
            else if (tecla == 27) {
                break;
            }
        }
    }

    void menuAgregarCancionGlobal() {
        std::string nTitulo, nAutor, nGenero;
        int nDuracion;

        BorrarPantallaEscribible();
        mostrarCursor();

        std::cout << "\033[38;2;146;208;80m";
        gotoxy(10, 30); std::cout << "--- AGREGAR NUEVA CANCION ---";
        std::cout << "\033[0m";

        gotoxy(12, 15); std::cout << "Titulo (usa_guiones): "; std::cin >> nTitulo;
        gotoxy(13, 15); std::cout << "Autor  (usa_guiones): "; std::cin >> nAutor;
        gotoxy(14, 15); std::cout << "Genero (usa_guiones): "; std::cin >> nGenero;
        gotoxy(15, 15); std::cout << "Duracion (segundos):  "; std::cin >> nDuracion;

        Cancion nuevaCancion(nTitulo, nAutor, nGenero, nDuracion);
        listaCancionesGlobales.agregarAlFinal(nuevaCancion);
        colaReproduccion.encolar(nuevaCancion);
        guardarCanciones();

        gotoxy(18, 15); std::cout << "\033[38;2;146;208;80mCancion agregada exitosamente!\033[0m";
        ocultarCursor();
        _getch();
    }

    void menuEliminarCancionGlobal() {
        std::string tituloEliminar;
        BorrarPantallaEscribible();
        mostrarCursor();

        std::cout << "\033[38;2;255;0;0m";
        gotoxy(10, 34); std::cout << "--- ELIMINAR CANCION ---";
        std::cout << "\033[0m";

        gotoxy(12, 15); std::cout << "Ingrese el Titulo exacto a eliminar: ";
        std::cin >> tituloEliminar;

        bool encontrado = false;
        Nodo<Cancion>* actual = listaCancionesGlobales.getInicio();
        int indice = 0;

        if (actual != nullptr) {
            do {
                if (actual->dato.getTitulo() == tituloEliminar) {
                    listaCancionesGlobales.eliminarEnPosicion(indice);
                    encontrado = true;
                    guardarCanciones();
                    gotoxy(15, 15); std::cout << "\033[38;2;146;208;80mCancion eliminada correctamente.\033[0m";
                    break;
                }
                actual = actual->siguiente;
                indice++;
            } while (actual != listaCancionesGlobales.getInicio());
        }

        if (!encontrado) {
            gotoxy(15, 15); std::cout << "\033[38;2;255;0;0mError: No se encontro la cancion.\033[0m";
        }

        ocultarCursor();
        _getch();
    }

    void guardarCanciones() {
        std::ofstream archivo(nombreArchivoCanciones);
        if (archivo.is_open()) {
            Nodo<Cancion>* actual = listaCancionesGlobales.getInicio();
            if (actual != nullptr) {
                do {
                    archivo << actual->dato.getTitulo() << " " << actual->dato.getAutor() << " "
                        << actual->dato.getGenero() << " " << actual->dato.getDuracion() << "\n";
                    actual = actual->siguiente;
                } while (actual != listaCancionesGlobales.getInicio());
            }
            archivo.close();
        }
    }

    void cargarUsuarios() {
        std::ifstream archivo(nombreArchivoUsuarios);
        if (archivo.is_open()) {
            std::string id, nombre, correo, pass;
            while (archivo >> id >> nombre >> correo >> pass) {
                Usuario u(id, nombre, correo, pass);
                listaUsuarios.agregarAlFinal(u);
            }
            archivo.close();
        }
    }

    void guardarUsuarios() {
        std::ofstream archivo(nombreArchivoUsuarios);
        if (archivo.is_open()) {
            Nodo<Usuario>* actual = listaUsuarios.getInicio();
            if (actual != nullptr) {
                do {
                    archivo << actual->dato.getId() << " "
                        << actual->dato.getNombreUsuario() << " "
                        << actual->dato.getCorreo() << " "
                        << actual->dato.getContrasena() << "\n";
                    actual = actual->siguiente;
                } while (actual != listaUsuarios.getInicio());
            }
            archivo.close();
        }
    }

    void menuRegistrarUsuario() {
        std::string nId, nNombre, nCorreo, nPass;
        BorrarPantallaEscribible();
        std::cout << "\033[38;2;146;208;80m";
        gotoxy(13, 32); std::cout << "--- REGISTRO DE USUARIO ---";
        gotoxy(14, 32); std::cout << "Ingrese ID: "; std::cin >> nId;

        bool existe = false;
        Nodo<Usuario>* actual = listaUsuarios.getInicio();

        if (actual != nullptr) {
            do {
                if (actual->dato.getId() == nId) {
                    existe = true;
                    break;
                }
                actual = actual->siguiente;
            } while (actual != listaUsuarios.getInicio());
        }

        if (existe) {
            gotoxy(16, 25); std::cout << "Error: Ya existe un usuario con el ID " << nId;
        }
        else {
            gotoxy(15, 32); std::cout << "Ingrese Nombre: "; std::cin >> nNombre;
            gotoxy(16, 32); std::cout << "Ingrese Correo: "; std::cin >> nCorreo;
            gotoxy(17, 32); std::cout << "Ingrese Contrasena: "; std::cin >> nPass;

            Usuario nuevoUsuario(nId, nNombre, nCorreo, nPass);
            listaUsuarios.agregarAlFinal(nuevoUsuario);
            guardarUsuarios();
            gotoxy(19, 32); std::cout << "Usuario registrado con exito!";
        }
        std::cout << "\033[0m";
    }

    void menuEliminarUsuario() {
        std::string idEliminar;
        BorrarPantallaEscribible();
        std::cout << "\033[38;2;146;208;80m";

        gotoxy(13, 34); std::cout << "--- ELIMINAR USUARIO ---";
        gotoxy(14, 34); std::cout << "Ingrese ID a eliminar: ";
        std::cin >> idEliminar;

        bool encontrado = false;
        Nodo<Usuario>* actual = listaUsuarios.getInicio();
        int indice = 0;

        if (actual != nullptr) {
            do {
                if (actual->dato.getId() == idEliminar) {
                    listaUsuarios.eliminarEnPosicion(indice);
                    encontrado = true;
                    guardarUsuarios();
                    gotoxy(16, 34); std::cout << "Usuario eliminado correctamente.";
                    break;
                }
                actual = actual->siguiente;
                indice++;
            } while (actual != listaUsuarios.getInicio());
        }

        if (!encontrado) {
            gotoxy(16, 34); std::cout << "Error: No se encontro ningun usuario con ese ID.";
        }
        std::cout << "\033[0m";
    }

    void menuIniciarSesion() {
        std::string idBuscado, passIngresada;
        BorrarPantallaEscribible();
        std::cout << "\033[38;2;146;208;80m";

        gotoxy(13, 37); std::cout << "Ingrese ID: ";
        std::cin >> idBuscado;

        bool encontrado = false;
        Nodo<Usuario>* actual = listaUsuarios.getInicio();

        if (actual != nullptr) {
            do {
                if (actual->dato.getId() == idBuscado) {
                    encontrado = true;
                    gotoxy(14, 37); std::cout << "Usuario encontrado";
                    gotoxy(15, 37); std::cout << "Ingrese contrasena: ";
                    gotoxy(16, 37);
                    std::cin >> passIngresada;

                    if (actual->dato.getContrasena() == passIngresada) {
                        gotoxy(17, 37); std::cout << "Bienvenido, " << actual->dato.getNombreUsuario() << "!";
                    }
                    else {
                        gotoxy(17, 37); std::cout << "Contrasena incorrecta.";
                    }
                    break;
                }
                actual = actual->siguiente;
            } while (actual != listaUsuarios.getInicio());
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
                if (indiceFondoIniciarSesion < 6) {
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
                case 4: menuVerCancionesGlobales(); _getch(); break;
                case 5: menuEliminarCancionGlobal(); _getch(); break;
                case 6: menuAgregarCancionGlobal(); _getch(); break;
                }
            }
            BorrarPantallaEscribible();
        }
    }
};