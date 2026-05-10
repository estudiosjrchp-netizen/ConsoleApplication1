#pragma once
#include <iostream>
#include <string>
#include "Lista1.h"
#include "Canciones.h" 

class Playlist {
private:
    std::string idPlaylist;
    std::string nombre;
    std::string descripcion;
    Lista1<Cancion> canciones; // Lista de canciones

public:
    Playlist(std::string _id = "", std::string _nombre = "", std::string _descripcion = "") {
        idPlaylist = _id;
        nombre = _nombre;
        descripcion = _descripcion;
    }

    // Getters y Setters
    std::string getId() const { return idPlaylist; }
    std::string getNombre() const { return nombre; }
    std::string getDescripcion() const { return descripcion; }

    void setNombre(std::string _nombre) { nombre = _nombre; }
    void setDescripcion(std::string _descripcion) { descripcion = _descripcion; }
    void setIDPlaylist(std::string _idPlaylist) { idPlaylist = _idPlaylist; }

    // Métodos
    void agregarCancion(Cancion nuevaCancion) {
        canciones.agregarAlFinal(nuevaCancion);
    }

    void mostrarPlaylist() const {
        //aca tengo la intencion de hacer algo chevere que se ponga en verdesito la seleccion en el fondo que hice pero sino se puede o mi coco no da pues fue; xd;

    }
};