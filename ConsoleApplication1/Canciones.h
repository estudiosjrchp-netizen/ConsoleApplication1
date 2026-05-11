#pragma once
#include "Dependencias.h"

class Cancion {
private:
    std::string titulo;
    std::string autor;
    std::string genero;
    int duracionSegundos;
    bool fav;
public:
    Cancion(std::string _titulo = "", std::string _autor = "", std::string _genero = "", int _duracion = 0) {
        titulo = _titulo;
        autor = _autor;
        genero = _genero;
        duracionSegundos = _duracion;
        fav = false;
    }

    std::string getTitulo() const { return titulo; }
    std::string getAutor() const { return autor; }
    std::string getGenero() const { return genero; }
    int getDuracion() const { return duracionSegundos; }

    void setTitulo(std::string _titulo) { titulo = _titulo; }
    void setAutor(std::string _autor) { autor = _autor; }
    void setGenero(std::string _genero) { genero = _genero; }
    void setDuracion(int _duracion) { duracionSegundos = _duracion; }

    bool getF() { return fav; }
    void setF(bool f) { fav = f; }

    void mostrar() const {
        std::cout << titulo << " - " << autor << " (" << genero << ") [" << duracionSegundos << "s]" << std::endl;
    }
};

