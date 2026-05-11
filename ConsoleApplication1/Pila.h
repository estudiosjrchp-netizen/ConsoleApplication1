#pragma once

template <typename T>
struct NodoPila {
    T dato;
    NodoPila* siguiente;
    NodoPila(T d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
class Pila {
private:
    NodoPila<T>* tope;
public:
    Pila() : tope(nullptr) {}
    ~Pila() {
        while (!vacia()) {
            pop();
        }
    }
    void push(T dato) {
        NodoPila<T>* nuevo = new NodoPila<T>(dato);
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    void pop() {
        if (tope) {
            NodoPila<T>* aux = tope;
            tope = tope->siguiente;
            delete aux;
        }
    }
    T top() { return tope->dato; }
    bool vacia() { return tope == nullptr; }
};