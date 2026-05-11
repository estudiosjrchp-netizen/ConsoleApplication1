#pragma once
#include <fstream>
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
    std::string nombreArchivoUsuarios = "usuarios.txt";
    std::vector<Cancion> listaCancionesGlobales;
    std::string nombreArchivoCanciones = "canciones.txt";

public:
	Controladora() {
        cargarUsuarios();
        cargarCanciones();
    };
	~Controladora() {};

    void cargarCanciones() {
        std::ifstream archivo(nombreArchivoCanciones);
        if (archivo.is_open()) {
            std::string titulo, autor, genero;
            int duracion;
            while (archivo >> titulo >> autor >> genero >> duracion) {
                Cancion c(titulo, autor, genero, duracion);
                listaCancionesGlobales.push_back(c);
            }
            archivo.close();
        }
    }

    void menuVerCancionesGlobales() {
        int paginaActual = 0;
        int cancionesPorPagina = 10; // Máximo para que no se salga de la pantalla escribible

        while (true) {
            BorrarPantallaEscribible();
            int totalPaginas = (listaCancionesGlobales.size() + cancionesPorPagina - 1) / cancionesPorPagina;
            if (totalPaginas == 0) totalPaginas = 1;

            std::cout << "\033[38;2;146;208;80m"; // verde spotify
            gotoxy(10, 30); std::cout << "--- REPOSITORIO GENERAL (" << paginaActual + 1 << "/" << totalPaginas << ") ---";
            std::cout << "\033[0m";

            int inicio = paginaActual * cancionesPorPagina;
            int fin = std::min(inicio + cancionesPorPagina, (int)listaCancionesGlobales.size());

            // Imprimir las canciones de la página actual
            for (int i = inicio; i < fin; i++) {
                gotoxy(12 + (i - inicio), 15); // Empieza en la fila 12 y baja hasta la 21
                std::cout << i + 1 << ". " << listaCancionesGlobales[i].getTitulo() << " - "
                    << listaCancionesGlobales[i].getAutor() << " (" << listaCancionesGlobales[i].getDuracion() << "s)";
            }

            // Controles
            std::cout << "\033[38;2;255;255;0m"; // Amarillo
            gotoxy(23, 15); std::cout << "[A] Atras | [D] Siguiente | [ESC] Salir";
            std::cout << "\033[0m";

            char tecla = _getch();
            if ((tecla == 'a' || tecla == 'A') && paginaActual > 0) {
                paginaActual--;
            }
            else if ((tecla == 'd' || tecla == 'D') && paginaActual < totalPaginas - 1) {
                paginaActual++;
            }
            else if (tecla == 27) { // 27 es el código ASCII para ESC
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
        listaCancionesGlobales.push_back(nuevaCancion);
        guardarCanciones();

        gotoxy(18, 15); std::cout << "\033[38;2;146;208;80mCancion agregada exitosamente!\033[0m";
        ocultarCursor();
        _getch();
    }

    void menuEliminarCancionGlobal() {
        std::string tituloEliminar;
        BorrarPantallaEscribible();
        mostrarCursor();

        std::cout << "\033[38;2;255;0;0m"; // Rojo para eliminar
        gotoxy(10, 34); std::cout << "--- ELIMINAR CANCION ---";
        std::cout << "\033[0m";

        gotoxy(12, 15); std::cout << "Ingrese el Titulo exacto a eliminar: ";
        std::cin >> tituloEliminar;

        bool encontrado = false;
        for (size_t i = 0; i < listaCancionesGlobales.size(); i++) {
            if (listaCancionesGlobales[i].getTitulo() == tituloEliminar) {
                listaCancionesGlobales.erase(listaCancionesGlobales.begin() + i);
                encontrado = true;
                guardarCanciones();
                gotoxy(15, 15); std::cout << "\033[38;2;146;208;80mCancion eliminada correctamente.\033[0m";
                break;
            }
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
            for (const Cancion& c : listaCancionesGlobales) {
                archivo << c.getTitulo() << " " << c.getAutor() << " "
                    << c.getGenero() << " " << c.getDuracion() << "\n";
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
                listaUsuarios.push_back(u);
            }
            archivo.close();
        }
    }

    void guardarUsuarios() {
        std::ofstream archivo(nombreArchivoUsuarios); 
        if (archivo.is_open()) {
            for (const Usuario& u : listaUsuarios) {
                archivo << u.getId() << " "
                    << u.getNombreUsuario() << " "
                    << u.getCorreo() << " "
                    << u.getContrasena() << "\n";
            }
            archivo.close();
        }
    }

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
            gotoxy(16, 25); std::cout << "Error: Ya existe un usuario con el ID " << nId;
        }
        else {
            // Si no existe, pedimos el resto de datos
            gotoxy(15, 32); std::cout << "Ingrese Nombre: "; std::cin >> nNombre;
            gotoxy(16, 32); std::cout << "Ingrese Correo: "; std::cin >> nCorreo;
            gotoxy(17, 32); std::cout << "Ingrese Contrasena: "; std::cin >> nPass;

            // Creamos el usuario y lo metemos al vector
            Usuario nuevoUsuario(nId, nNombre, nCorreo, nPass);
            listaUsuarios.push_back(nuevoUsuario);
            guardarUsuarios();
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
                guardarUsuarios(); //guardamos los usuarios
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

