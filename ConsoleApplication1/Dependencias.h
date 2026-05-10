#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "matrices.h"

//codigos ansii para no mostrar el cursor y mostrarlo;
void ocultarCursor() {
    std::cout << "\033[?25l";
    std::cout << std::flush;
}

void mostrarCursor() {
    std::cout << "\033[?25h";
    std::cout << std::flush;
}
//nodo para formar lista1 hagan otros nodos si usaran otro tipo de lita o usen esto si quieren xd aunque creo que se puede confundir un poco :v;
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(T _dato) {
        dato = _dato;
        siguiente = nullptr;
        anterior = nullptr;
    }
};


//Funcion imprimir Matriz //nota, esta cosa es insufriblemente lenta; creare una funcion actualizar matriz mas rapida;
void ImprimirMatrizFondo(const vvi& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz.at(0).size(); j++) {
           
            if (matriz[i][j] != 0) {
                gotoxy(i, j);
                switch (matriz[i][j])
                {
                case 1: std::cout << "\033[38;2;255;255;255m"; break; // blanco 
                case 2: std::cout << "\033[38;2;255;0;0m"; break; // ROJO
                case 3: std::cout << "\033[38;2;146;208;80m"; break; // verde spotify
                default:
                    std::cout << "\033[0m"; // Resetear las cosas por defecto por si hay algun defecto xd :v
                    break;
                }
                std::cout << static_cast<char>(219);
                std::cout << "\033[0m"; // Resetear color al original
            }
            else {
                std::cout << " ";
            }
        }
    }
}
//esto hara que actualizar el fondo sea un poco mas rapido; 
void ActualizarMatrizFondo(const vvi& matriz_fondo, const vvi& matriz_nueva) {
    for (int i = 0; i < matriz_nueva.size(); i++) {
        for (int j = 0; j < matriz_nueva.at(0).size(); j++) {
            if (matriz_fondo[i][j] != matriz_nueva[i][j]) {
                gotoxy(i, j); //primero filas y luego columnas
                if (matriz_nueva[i][j] != 0) {
                    switch (matriz_nueva[i][j])
                    {
                    case 1: std::cout << "\033[38;2;255;255;255m"; break; // blanco 
                    case 2: std::cout << "\033[38;2;255;0;0m"; break; // ROJO
                    case 3: std::cout << "\033[38;2;146;208;80m"; break; // verde spotify
                    default:
                        std::cout << "\033[0m"; // Resetear las cosas por defecto por si hay algun defecto xd :v
                        break;
                    }
                    std::cout << static_cast<char>(219);
                    std::cout << "\033[0m"; // Resetear color al original
                }
                else {
                    std::cout << " ";
                }
            }

        }
    }
}
// Imprime una matriz mas pequeña (por ejemplo una ventana) encima del fondo en unas coordenadas dadas
void ImprimirMatrizEncima(const vvi& matriz_encima, int fila_inicio, int col_inicio) {
    for (int i = 0; i < matriz_encima.size(); i++) {
        for (int j = 0; j < matriz_encima[0].size(); j++) {
            gotoxy(fila_inicio + i, col_inicio + j);
            if (matriz_encima[i][j] != 0) {
                switch (matriz_encima[i][j])
                {
                case 1: std::cout << "\033[38;2;255;255;255m"; break; // blanco 
                case 2: std::cout << "\033[38;2;255;0;0m"; break; // ROJO
                case 3: std::cout << "\033[38;2;146;208;80m"; break; // verde spotify
                default:
                    std::cout << "\033[0m"; break;
                }
                std::cout << static_cast<char>(219);
                std::cout << "\033[0m"; // Resetear color al original
            }
            else {
                std::cout << " ";
            }
        }
    }
}
// Borra la matriz que esta encima, restaurando el pedazo de fondo original que habia en esas coordenadas
// Necesita al de el tamaño de la matriz q estorbaba o la matriz misma
void BorrarMatrizEncima(const vvi& matriz_encima, const vvi& matriz_fondo_completo, int fila_inicio, int col_inicio) {
    for (int i = 0; i < matriz_encima.size(); i++) {
        for (int j = 0; j < matriz_encima[0].size(); j++) {
            // Asegurarnos de que no nos salimos del fondo
            if (fila_inicio + i < matriz_fondo_completo.size() && col_inicio + j < matriz_fondo_completo[0].size()) {
                gotoxy(fila_inicio + i, col_inicio + j);
                if (matriz_fondo_completo[fila_inicio + i][col_inicio + j] != 0) {
                    switch (matriz_fondo_completo[fila_inicio + i][col_inicio + j])
                    {
                    case 1: std::cout << "\033[38;2;255;255;255m"; break; // blanco 
                    case 2: std::cout << "\033[38;2;255;0;0m"; break; // ROJO
                    case 3: std::cout << "\033[38;2;146;208;80m"; break; // verde spotify
                    default:
                        std::cout << "\033[0m"; break;
                    }
                    std::cout << static_cast<char>(219);
                    std::cout << "\033[0m";
                }
                else {
                    std::cout << " ";
                }
            }
        }
    }
}




