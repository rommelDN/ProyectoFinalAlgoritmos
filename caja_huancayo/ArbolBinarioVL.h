#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

template<class T>
class Nodo {
public:
    T elemento;
    Nodo* izq;
    Nodo* der;
    int altura;
    Nodo(const T& val) : elemento(val), izq(nullptr), der(nullptr), altura(1) {}
};

template<class T>
class ArbolAVL {
    typedef function<int(T, T)> Comp;
    Nodo<T>* raiz;
    void(*procesar)(T);
    Comp comparar;

private:
    bool _vacio() { return raiz == nullptr; }
    int alturaNodo(Nodo<T>* nodo) {
        return nodo ? nodo->altura : 0;
    }
    void actualizarAltura(Nodo<T>* nodo) {
        if (nodo) nodo->altura = 1 + max(alturaNodo(nodo->izq), alturaNodo(nodo->der));
    }
    int factorBalance(Nodo<T>* nodo) {
        if (!nodo) return 0;
        return alturaNodo(nodo->izq) - alturaNodo(nodo->der);
    }
    Nodo<T>* rotacionDerecha(Nodo<T>* y) {
        Nodo<T>* x = y->izq;
        Nodo<T>* T2 = x->der;
        x->der = y;
        y->izq = T2;
        actualizarAltura(y);
        actualizarAltura(x);
        return x;
    }
    Nodo<T>* rotacionIzquierda(Nodo<T>* x) {
        Nodo<T>* y = x->der;
        Nodo<T>* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        actualizarAltura(x);
        actualizarAltura(y);
        return y;
    }
    Nodo<T>* balancear(Nodo<T>* nodo) {
        if (!nodo) return nodo;
        actualizarAltura(nodo);
        int fb = factorBalance(nodo);
        if (fb > 1 && factorBalance(nodo->izq) >= 0)return rotacionDerecha(nodo);
        if (fb > 1 && factorBalance(nodo->izq) < 0) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        if (fb < -1 && factorBalance(nodo->der) <= 0)return rotacionIzquierda(nodo);
        if (fb < -1 && factorBalance(nodo->der) > 0) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }
        return nodo;
    }
    pair<Nodo<T>*, bool> _insertarRec(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) {
            Nodo<T>* nuevo = new Nodo<T>(e);
            return { nuevo, true };
        }

        int r = comparar(nodo->elemento, e);
        if (r == 0) return { nodo, false };
        else if (r < 0) {
            auto res = _insertarRec(nodo->der, e);
            nodo->der = res.first;
        }
        else {
            auto res = _insertarRec(nodo->izq, e);
            nodo->izq = res.first;
        }
        Nodo<T>* balanceado = balancear(nodo);
        return { balanceado, true }; 
    }
    bool _buscar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        int r = comparar(nodo->elemento, e);
        if (r == 0) return true;
        else if (r < 0) return _buscar(nodo->der, e);
        else return _buscar(nodo->izq, e);
    }
    Nodo<T>* _obtener(Nodo<T>* nodo, T e) {
        if (!nodo) return nullptr;
        int r = comparar(nodo->elemento, e);
        if (r == 0) return nodo;
        else if (r < 0) return _obtener(nodo->der, e);
        else return _obtener(nodo->izq, e);
    }
    Nodo<T>* nodoMinimo(Nodo<T>* nodo) {
        Nodo<T>* actual = nodo;
        while (actual && actual->izq) actual = actual->izq;
        return actual;
    }
    pair<Nodo<T>*, bool> _eliminarRec(Nodo<T>* nodo, T e) {
        if (!nodo) return { nullptr, false };
        int r = comparar(nodo->elemento, e);
        if (r < 0) {
            auto res = _eliminarRec(nodo->der, e);
            nodo->der = res.first;
            if (!res.second) return { nodo, false };
        }
        else if (r > 0) {
            auto res = _eliminarRec(nodo->izq, e);
            nodo->izq = res.first;
            if (!res.second) return { nodo, false };
        }
        else {
            if (!nodo->izq || !nodo->der) {
                Nodo<T>* temp = nodo->izq ? nodo->izq : nodo->der;
                if (!temp) {
                    delete nodo;
                    return { nullptr, true };
                }
                else {
                    Nodo<T>* reemplazo = temp;
                    delete nodo;
                    return { reemplazo, true };
                }
            }
            else {
                Nodo<T>* sucesor = nodoMinimo(nodo->der);
                nodo->elemento = sucesor->elemento;
                auto res = _eliminarRec(nodo->der, sucesor->elemento);
                nodo->der = res.first;
            }
        }
        Nodo<T>* balanceado = balancear(nodo);
        return { balanceado, true };
    }
    int _cantidad(Nodo<T>* nodo) {
        if (!nodo) return 0;
        return 1 + _cantidad(nodo->izq) + _cantidad(nodo->der);
    }
    int _altura(Nodo<T>* nodo) {
        return alturaNodo(nodo);
    }
    T _minimo(Nodo<T>* nodo) {
        Nodo<T>* n = nodoMinimo(nodo);
        if (!n) throw runtime_error("Arbol vacio");
        return n->elemento;
    }
    T _maximo(Nodo<T>* nodo) {
        Nodo<T>* actual = nodo;
        if (!actual) throw runtime_error("Arbol vacio");
        while (actual->der) actual = actual->der;
        return actual->elemento;
    }
    void _enOrden(Nodo<T>* nodo) {
        if (!nodo) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }
    void _preOrden(Nodo<T>* nodo) {
        if (!nodo) return;
        procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }
    void _postOrden(Nodo<T>* nodo) {
        if (!nodo) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        procesar(nodo->elemento);
    }
    T _sumarHojas(Nodo<T>* nodo) {
        if (!nodo) return (T)0;
        if (!nodo->izq && !nodo->der) return nodo->elemento;
        return _sumarHojas(nodo->izq) + _sumarHojas(nodo->der);
    }
    void _mostrarArbol(Nodo<T>* nodo, int nivel = 0) {
        if (!nodo) return;
        _mostrarArbol(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; ++i) cout << "  ";
        cout << nodo->elemento << " (h=" << nodo->altura << ")\n";
        _mostrarArbol(nodo->izq, nivel + 1);
    }
    void _liberar(Nodo<T>* nodo) {
        if (!nodo) return;
        _liberar(nodo->izq);
        _liberar(nodo->der);
        delete nodo;
    }
public:
    ArbolAVL(void(*otroPunteroFuncion)(T)) {
        this->procesar = otroPunteroFuncion;
        this->comparar = [](T a, T b) { return (a < b) ? -1 : (a > b) ? 1 : 0; };
        raiz = nullptr;
    }
    ~ArbolAVL() {
        _liberar(raiz);
        raiz = nullptr;
    }
    bool insertar(T e) {
        auto res = _insertarRec(raiz, e);
        raiz = res.first;
        return res.second;
    }
    bool Eliminar(T e) {
        auto res = _eliminarRec(raiz, e);
        raiz = res.first;
        return res.second;
    }

    bool Buscar(T e) {
        return _buscar(raiz, e);
    }

    Nodo<T>* Obtener(T e) {
        return _obtener(raiz, e);
    }

    void enOrden() { _enOrden(raiz); }
    void preOrden() { _preOrden(raiz); }
    void postOrden() { _postOrden(raiz); }

    int cantidad() { return _cantidad(raiz); }
    int altura() { return _altura(raiz); }

    T Minimo() { return _minimo(raiz); }
    T Maximo() { return _maximo(raiz); }

    T SumarHojas() { return _sumarHojas(raiz); }

    void mostrar() { _mostrarArbol(raiz); }

    // permite cambiar la comparación si lo deseas (por ejemplo comparator personalizado)
    void setComparador(Comp comp) { comparar = comp; }
};
