#pragma once
#include <iostream>
#include <string>
#include "Lista1.h"
#include "Playlist.h"

class Usuario {
private:
    std::string id;
    std::string nombreUsuario;
    std::string correo;
    std::string contrasena;
    Lista1<Playlist> misPlaylists;

public:
    Usuario(std::string _id = "", std::string _nombre = "", std::string _correo = "", std::string _contrasena = "") {
        id = _id;
        nombreUsuario = _nombre;
        correo = _correo;
        contrasena = _contrasena;
    }

    std::string getId() const { return id; }
    std::string getNombreUsuario() const { return nombreUsuario; }
    std::string getCorreo() const { return correo; }
    std::string getContrasena() const { return contrasena; }
    Lista1<Playlist>& getPlaylists() { return misPlaylists; }

    void setId(std::string _id) { id = _id; }
    void setNombreUsuario(std::string _nombre) { nombreUsuario = _nombre; }
    void setCorreo(std::string _correo) { correo = _correo; }
    void setContrasena(std::string _contrasena) { contrasena = _contrasena; }

    void mostrar() const {
        std::cout << "ID: " << id << " | Usuario: " << nombreUsuario << " | Correo: " << correo << std::endl;
    }
};