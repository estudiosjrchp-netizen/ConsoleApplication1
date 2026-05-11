#pragma once
#include <iostream>
#include <string>
#include "Lista1.h"
#include "Canciones.h" 
#include <functional> 

class Playlist {
private:
    std::string idPlaylist;
    std::string nombre;
    std::string descripcion;
    Lista1<Cancion> canciones;

public:
    Playlist(std::string _id = "", std::string _nombre = "", std::string _descripcion = "") {
        idPlaylist = _id;
        nombre = _nombre;
        descripcion = _descripcion;
    }

    std::string getId() const { return idPlaylist; }
    std::string getNombre() const { return nombre; }
    std::string getDescripcion() const { return descripcion; }

    void setNombre(std::string _nombre) { nombre = _nombre; }
    void setDescripcion(std::string _descripcion) { descripcion = _descripcion; }
    void setIDPlaylist(std::string _idPlaylist) { idPlaylist = _idPlaylist; }

    void agregarCancion(Cancion nuevaCancion) {
        canciones.agregarAlFinal(nuevaCancion);
    }

    Lista1<Cancion>& getCanciones() { return canciones; }

    void ordenarAlfabeticamente() {
        std::function<bool(Cancion, Cancion)> compAlfabetico = [](Cancion c1, Cancion c2) {
            return c1.getTitulo() > c2.getTitulo();
            };
        canciones.ordenar(compAlfabetico);
    }

    void ordenarGenero() {
        std::function<bool(Cancion, Cancion)> compGenero = [](Cancion c1, Cancion c2) {
            return c1.getGenero() > c2.getGenero();
            };
        canciones.ordenar(compGenero);
    }
};