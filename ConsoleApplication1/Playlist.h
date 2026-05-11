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
    //uso de ia para esto; :v era mas facil de lo que crei pero al fin y al cabo es ia :v.... aunque creo que las mayusculas podrian representar un problema 
    void ordenarAlfabeticamente() {

        // LÓGICA DE LA LAMBDA:
        // Declaramos explícitamente que compAlfabetico es una función que retorna bool
        // y recibe dos objetos Cancion.
        std::function<bool(Cancion, Cancion)> compAlfabetico = [](Cancion c1, Cancion c2) {
            // Comparamos los títulos. 
            // Si c1 es "Zebra" y c2 es "Avion", "Zebra" > "Avion" es TRUE.
            // Si devuelve TRUE, nuestra Lista1 sabrá que debe intercambiarlos.
            return c1.getTitulo() > c2.getTitulo();
            };

        // Le enviamos nuestra lambda a la lista de canciones
        canciones.ordenar(compAlfabetico);

        std::cout << "La playlist ha sido ordenada alfabeticamente!\n";
    }

    void ordenarGenero() {
        std::function<bool(Cancion, Cancion)> compGenero = [](Cancion c1, Cancion c2) {
            return c1.getGenero() > c2.getGenero();
            };
        canciones.ordenar(compGenero);
        std::cout << "La playlist ha sido ordenada por genero!\n";
    }
};