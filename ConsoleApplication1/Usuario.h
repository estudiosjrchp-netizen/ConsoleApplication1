#pragma once
#include <iostream>
#include <string>

class Usuario {
private:
    std::string id; //idea creamos un usario con id buscamos por id o por nombre 
    //en la consola luego para acceder a las cosas del usuario te pide la contra que la obtenemos usando la id osea creamos un puntero
    // auxiliar que almacene al usuario segun la id osea si la id es la del usuario y luego con ese usamos esa cosa para sacar la contraseña y
    // compararla con el imput y si sale pos entonces mostramos lo siguiente y si no mensaje de error :v
    std::string nombreUsuario;
    std::string correo;
    std::string contrasena;

public:
    Usuario(std::string _id = "", std::string _nombre = "", std::string _correo = "", std::string _contrasena = "") {
        id = _id;
        nombreUsuario = _nombre;
        correo = _correo;
        contrasena = _contrasena;
    }
    //getters
    std::string getId() const { return id; }
    std::string getNombreUsuario() const { return nombreUsuario; }
    std::string getCorreo() const { return correo; }
    std::string getContrasena() const { return contrasena; }
    //setters
    void setId(std::string _id) { id = _id; }
    void setNombreUsuario(std::string _nombre) { nombreUsuario = _nombre; }
    void setCorreo(std::string _correo) { correo = _correo; }
    void setContrasena(std::string _contrasena) { contrasena = _contrasena; }
    //metodos 
    void mostrar() const {
        std::cout << "ID: " << id << " | Usuario: " << nombreUsuario << " | Correo: " << correo << std::endl;
    }
};