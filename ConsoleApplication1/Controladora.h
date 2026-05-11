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

    void menuUsuarioActual(Usuario& usuario) {
        int opcion = 1;
        while (true) {
            BorrarPantallaEscribible();
            gotoxy(11, 30); std::cout << "\033[38;2;146;208;80m--- MENU DE " << usuario.getNombreUsuario() << " ---\033[0m";
            gotoxy(13, 30); std::cout << (opcion == 1 ? "\033[38;2;255;255;0m> " : "  ") << "1. Crear Playlist\033[0m";
            gotoxy(14, 30); std::cout << (opcion == 2 ? "\033[38;2;255;255;0m> " : "  ") << "2. Ver mis Playlists\033[0m";
            gotoxy(15, 30); std::cout << (opcion == 3 ? "\033[38;2;255;255;0m> " : "  ") << "3. Cerrar Sesion\033[0m";

            char tecla = _getch();
            if ((tecla == 'w' || tecla == 'W') && opcion > 1) opcion--;
            else if ((tecla == 's' || tecla == 'S') && opcion < 3) opcion++;
            else if (tecla == 13) {
                if (opcion == 1) {
                    crearPlaylistUsuario(usuario);
                }
                else if (opcion == 2) {
                    verPlaylistsUsuario(usuario);
                }
                else if (opcion == 3) {
                    break;
                }
            }
        }
    }

    void crearPlaylistUsuario(Usuario& usuario) {
        std::string nId, nNombre, nDesc;
        BorrarPantallaEscribible();
        mostrarCursor();
        gotoxy(12, 15); std::cout << "ID Playlist: "; std::cin >> nId;
        gotoxy(13, 15); std::cout << "Nombre (sin_espacios): "; std::cin >> nNombre;
        gotoxy(14, 15); std::cout << "Descripcion: "; std::cin >> nDesc;

        Playlist nueva(nId, nNombre, nDesc);
        usuario.getPlaylists().agregarAlFinal(nueva);

        gotoxy(16, 15); std::cout << "\033[38;2;146;208;80mPlaylist creada!\033[0m";
        ocultarCursor();
        _getch();
    }

    void verPlaylistsUsuario(Usuario& usuario) {
        if (usuario.getPlaylists().getCantidad() == 0) {
            BorrarPantallaEscribible();
            gotoxy(15, 15); std::cout << "\033[38;2;255;0;0mNo tienes playlists.\033[0m";
            _getch();
            return;
        }

        int opcion = 0;
        while (true) {
            BorrarPantallaEscribible();
            gotoxy(10, 30); std::cout << "\033[38;2;146;208;80m--- MIS PLAYLISTS ---\033[0m";

            Nodo<Playlist>* actual = usuario.getPlaylists().getInicio();
            for (int i = 0; i < usuario.getPlaylists().getCantidad(); i++) {
                gotoxy(12 + i, 15);
                if (i == opcion) std::cout << "\033[38;2;255;255;0m> " << actual->dato.getNombre() << "\033[0m";
                else std::cout << "  " << actual->dato.getNombre();
                actual = actual->siguiente;
            }

            char tecla = _getch();
            if ((tecla == 'w' || tecla == 'W') && opcion > 0) opcion--;
            else if ((tecla == 's' || tecla == 'S') && opcion < usuario.getPlaylists().getCantidad() - 1) opcion++;
            else if (tecla == 13) {
                Nodo<Playlist>* seleccionada = usuario.getPlaylists().getInicio();
                for (int i = 0; i < opcion; i++) seleccionada = seleccionada->siguiente;
                gestionarPlaylist(seleccionada->dato);
            }
            else if (tecla == 27) break;
        }
    }

    void gestionarPlaylist(Playlist& playlist) {
        int opcion = 1;
        while (true) {
            BorrarPantallaEscribible();
            gotoxy(10, 30); std::cout << "\033[38;2;146;208;80m--- PLAYLIST: " << playlist.getNombre() << " ---\033[0m";
            gotoxy(12, 30); std::cout << (opcion == 1 ? "\033[38;2;255;255;0m> " : "  ") << "1. Ver Canciones\033[0m";
            gotoxy(13, 30); std::cout << (opcion == 2 ? "\033[38;2;255;255;0m> " : "  ") << "2. Agregar Cancion (Global)\033[0m";
            gotoxy(14, 30); std::cout << (opcion == 3 ? "\033[38;2;255;255;0m> " : "  ") << "3. Ordenar Alfabeticamente\033[0m";
            gotoxy(15, 30); std::cout << (opcion == 4 ? "\033[38;2;255;255;0m> " : "  ") << "4. Ordenar por Genero\033[0m";
            gotoxy(16, 30); std::cout << (opcion == 5 ? "\033[38;2;255;255;0m> " : "  ") << "5. Volver\033[0m";

            char tecla = _getch();
            if ((tecla == 'w' || tecla == 'W') && opcion > 1) opcion--;
            else if ((tecla == 's' || tecla == 'S') && opcion < 5) opcion++;
            else if (tecla == 13) {
                if (opcion == 1) {
                    mostrarCancionesPlaylist(playlist);
                }
                else if (opcion == 2) {
                    agregarCancionAPlaylist(playlist);
                }
                else if (opcion == 3) {
                    playlist.ordenarAlfabeticamente();
                    BorrarPantallaEscribible();
                    gotoxy(15, 15); std::cout << "\033[38;2;146;208;80mOrdenado alfabeticamente!\033[0m";
                    _getch();
                }
                else if (opcion == 4) {
                    playlist.ordenarGenero();
                    BorrarPantallaEscribible();
                    gotoxy(15, 15); std::cout << "\033[38;2;146;208;80mOrdenado por genero!\033[0m";
                    _getch();
                }
                else if (opcion == 5) {
                    break;
                }
            }
        }
    }

    void mostrarCancionesPlaylist(Playlist& playlist) {
        if (playlist.getCanciones().getCantidad() == 0) {
            BorrarPantallaEscribible();
            gotoxy(15, 15); std::cout << "\033[38;2;255;0;0mLa playlist esta vacia.\033[0m";
            _getch();
            return;
        }

        int paginaActual = 0;
        int cancionesPorPagina = 10;
        while (true) {
            BorrarPantallaEscribible();
            int total = playlist.getCanciones().getCantidad();
            int totalPaginas = (total + cancionesPorPagina - 1) / cancionesPorPagina;

            gotoxy(10, 30); std::cout << "\033[38;2;146;208;80m--- CANCIONES (" << paginaActual + 1 << "/" << totalPaginas << ") ---\033[0m";

            int inicio = paginaActual * cancionesPorPagina;
            int fin = std::min(inicio + cancionesPorPagina, total);

            Nodo<Cancion>* actual = playlist.getCanciones().getInicio();
            for (int i = 0; i < inicio && actual != nullptr; i++) actual = actual->siguiente;

            for (int i = inicio; i < fin && actual != nullptr; i++) {
                gotoxy(12 + (i - inicio), 15);
                std::cout << i + 1 << ". " << actual->dato.getTitulo() << " - " << actual->dato.getAutor() << " (" << actual->dato.getGenero() << ")";
                actual = actual->siguiente;
            }

            gotoxy(23, 15); std::cout << "\033[38;2;255;255;0m[A] Atras | [D] Siguiente | [ESC] Volver\033[0m";

            char tecla = _getch();
            if ((tecla == 'a' || tecla == 'A') && paginaActual > 0) paginaActual--;
            else if ((tecla == 'd' || tecla == 'D') && paginaActual < totalPaginas - 1) paginaActual++;
            else if (tecla == 27) break;
        }
    }

    void agregarCancionAPlaylist(Playlist& playlist) {
        std::string tituloBuscado;
        BorrarPantallaEscribible();
        mostrarCursor();
        gotoxy(12, 15); std::cout << "Escribe el titulo exacto de la cancion: ";
        std::cin >> tituloBuscado;

        bool encontrada = false;
        Nodo<Cancion>* actual = listaCancionesGlobales.getInicio();
        if (actual != nullptr) {
            do {
                if (actual->dato.getTitulo() == tituloBuscado) {
                    playlist.agregarCancion(actual->dato);
                    encontrada = true;
                    break;
                }
                actual = actual->siguiente;
            } while (actual != listaCancionesGlobales.getInicio());
        }

        BorrarPantallaEscribible();
        if (encontrada) {
            gotoxy(15, 15); std::cout << "\033[38;2;146;208;80mCancion agregada a la playlist!\033[0m";
        }
        else {
            gotoxy(15, 15); std::cout << "\033[38;2;255;0;0mNo se encontro la cancion en el sistema.\033[0m";
        }
        ocultarCursor();
        _getch();
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
                        menuUsuarioActual(actual->dato);
                    }
                    else {
                        gotoxy(17, 37); std::cout << "Contrasena incorrecta.";
                        _getch();
                    }
                    break;
                }
                actual = actual->siguiente;
            } while (actual != listaUsuarios.getInicio());
        }

        if (!encontrado) {
            gotoxy(16, 37); std::cout << "El usuario no existe.";
            _getch();
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
                case 1: menuIniciarSesion(); break;
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