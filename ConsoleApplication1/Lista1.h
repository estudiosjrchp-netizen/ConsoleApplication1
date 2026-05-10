#pragma once
#include "Dependencias.h"
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

};
