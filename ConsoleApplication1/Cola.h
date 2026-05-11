#pragma once

template <typename T>
struct NodoCola {
    T dato;
    NodoCola* siguiente;
    NodoCola(T d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
class Cola {
private:
    NodoCola<T>* frente;
    NodoCola<T>* finalCola;
public:
    Cola() : frente(nullptr), finalCola(nullptr) {}
    ~Cola() {
        while (!vacia()) {
            desencolar();
        }
    }
    void encolar(T dato) {
        NodoCola<T>* nuevo = new NodoCola<T>(dato);
        if (vacia()) {
            frente = finalCola = nuevo;
        }
        else {
            finalCola->siguiente = nuevo;
            finalCola = nuevo;
        }
    }
    void desencolar() {
        if (frente) {
            NodoCola<T>* aux = frente;
            frente = frente->siguiente;
            if (!frente) finalCola = nullptr;
            delete aux;
        }
    }
    T front() { return frente->dato; }
    bool vacia() { return frente == nullptr; }
};