#pragma once
#include "Dependencias.h"
#include <functional>
//lista circular doblemente enlazada pa que vean hijitos
template <typename T>
class Lista1 {
private:
    Nodo<T>* inicio;
    Nodo<T>* fin;
    int cantidad;

public:
    Lista1() {
        inicio = nullptr;
        fin = nullptr;
        cantidad = 0;
    }

    ~Lista1() {
        if (inicio == nullptr) return;
        Nodo<T>* actual = inicio;
        do {
            Nodo<T>* aBorrar = actual;
            actual = actual->siguiente;
            delete aBorrar;
        } while (actual != inicio);
    }

    int getCantidad() const { return cantidad; }
    Nodo<T>* getInicio() const { return inicio; }
    Nodo<T>* getFin() const { return fin; }

    void agregarAlInicio(T dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if (inicio == nullptr) {
            inicio = fin = nuevoNodo;
            inicio->siguiente = inicio;
            inicio->anterior = inicio;
        }
        else {
            nuevoNodo->siguiente = inicio;
            nuevoNodo->anterior = fin;
            inicio->anterior = nuevoNodo;
            fin->siguiente = nuevoNodo;
            inicio = nuevoNodo;
        }
        cantidad++;
    }

    void agregarAlFinal(T dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if (inicio == nullptr) {
            inicio = fin = nuevoNodo;
            inicio->siguiente = inicio;
            inicio->anterior = inicio;
        }
        else {
            fin->siguiente = nuevoNodo;
            nuevoNodo->anterior = fin;
            nuevoNodo->siguiente = inicio;
            inicio->anterior = nuevoNodo;
            fin = nuevoNodo;
        }
        cantidad++;
    }

    bool agregarEnPosicion(int pos, T dato) {
        if (pos < 0 || pos > cantidad) return false;

        if (pos == 0) {
            agregarAlInicio(dato);
            return true;
        }
        if (pos == cantidad) {
            agregarAlFinal(dato);
            return true;
        }

        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        Nodo<T>* actual = inicio;
        for (int i = 0; i < pos; i++) {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual;
        nuevoNodo->anterior = actual->anterior;
        actual->anterior->siguiente = nuevoNodo;
        actual->anterior = nuevoNodo;

        cantidad++;
        return true;
    }

    bool eliminarEnPosicion(int pos) {
        if (pos < 0 || pos >= cantidad || inicio == nullptr) return false;

        Nodo<T>* aBorrar = inicio;

        if (cantidad == 1) {
            inicio = nullptr;
            fin = nullptr;
        }
        else if (pos == 0) {
            inicio = inicio->siguiente;
            inicio->anterior = fin;
            fin->siguiente = inicio;
        }
        else if (pos == cantidad - 1) {
            aBorrar = fin;
            fin = fin->anterior;
            fin->siguiente = inicio;
            inicio->anterior = fin;
        }
        else {
            for (int i = 0; i < pos; i++) {
                aBorrar = aBorrar->siguiente;
            }

            aBorrar->anterior->siguiente = aBorrar->siguiente;
            aBorrar->siguiente->anterior = aBorrar->anterior;
        }

        delete aBorrar;
        cantidad--;
        return true;
    }

    //esta wea la cree para ordenamiento alfabetico pero puede servir para cualquier cosa por el functional 
    void ordenar(std::function<bool(T, T)> comparador) {
        // Si la lista está vacía o solo tiene 1 elemento, ya está ordenada
        if (inicio == nullptr || inicio == fin) return;

        bool intercambiado;
        do {
            intercambiado = false;
            Nodo<T>* actual = inicio;

            // Recorremos la lista circular
            do {
                Nodo<T>* siguiente = actual->siguiente;

                // Evitamos comparar el último nodo con el inicio en este ciclo
                if (siguiente != inicio) {

                    // Aquí usamos el primer lambda el alfabetico 
                    //si devuelve true los cambiamos
                    if (comparador(actual->dato, siguiente->dato)) {

                        // Intercambiamos solo los 'datos' (es más fácil que mover los nodos enteros)
                        T temp = actual->dato;
                        actual->dato = siguiente->dato;
                        siguiente->dato = temp;

                        intercambiado = true; // Hubo un cambio, así que repetiremos el ciclo
                    }
                }
                actual = actual->siguiente;
            } while (actual->siguiente != inicio); // Paramos cuando damos la vuelta

        } while (intercambiado); // Si en toda una vuelta no intercambiamos nada, ya está ordenado
    }

}; 


