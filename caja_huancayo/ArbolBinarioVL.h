#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

template<class T>
class NodoAVL {
public:
    T elemento;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
    NodoAVL(const T& val) : elemento(val), izq(nullptr), der(nullptr), altura(1) {}
};

template<class T>
class ArbolAVL {
    typedef function<int(T, T)> Comp;
    NodoAVL<T>* raiz;
    void(*procesar)(T);
    Comp comparar;

private:
    bool _vacio() { return raiz == nullptr; }
    int alturaNodo(NodoAVL<T>* nodo) {
        return nodo ? nodo->altura : 0;
    }
    void actualizarAltura(NodoAVL<T>* nodo) {
        if (nodo) nodo->altura = 1 + max(alturaNodo(nodo->izq), alturaNodo(nodo->der));
    }
    int factorBalance(NodoAVL<T>* nodo) {
        if (!nodo) return 0;
        return alturaNodo(nodo->izq) - alturaNodo(nodo->der);
    }
    NodoAVL<T>* rotacionDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izq;
        NodoAVL<T>* T2 = x->der;
        x->der = y;
        y->izq = T2;
        actualizarAltura(y);
        actualizarAltura(x);
        return x;
    }
    NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->der;
        NodoAVL<T>* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        actualizarAltura(x);
        actualizarAltura(y);
        return y;
    }
    NodoAVL<T>* balancear(NodoAVL<T>* nodo) {
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
    pair<NodoAVL<T>*, bool> _insertarRec(NodoAVL<T>* nodo, T e) {
        if (nodo == nullptr) {
            NodoAVL<T>* nuevo = new NodoAVL<T>(e);
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
        NodoAVL<T>* balanceado = balancear(nodo);
        return { balanceado, true };
    }
    bool _buscar(NodoAVL<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        int r = comparar(nodo->elemento, e);
        if (r == 0) return true;
        else if (r < 0) return _buscar(nodo->der, e);
        else return _buscar(nodo->izq, e);
    }
    NodoAVL<T>* _obtener(NodoAVL<T>* nodo, T e) {
        if (!nodo) return nullptr;
        int r = comparar(nodo->elemento, e);
        if (r == 0) return nodo;
        else if (r < 0) return _obtener(nodo->der, e);
        else return _obtener(nodo->izq, e);
    }
    NodoAVL<T>* nodoMinimo(NodoAVL<T>* nodo) {
        NodoAVL<T>* actual = nodo;
        while (actual && actual->izq) actual = actual->izq;
        return actual;
    }
    pair<NodoAVL<T>*, bool> _eliminarRec(NodoAVL<T>* nodo, T e) {
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
                NodoAVL<T>* temp = nodo->izq ? nodo->izq : nodo->der;
                if (!temp) {
                    delete nodo;
                    return { nullptr, true };
                }
                else {
                    NodoAVL<T>* reemplazo = temp;
                    delete nodo;
                    return { reemplazo, true };
                }
            }
            else {
                NodoAVL<T>* sucesor = nodoMinimo(nodo->der);
                nodo->elemento = sucesor->elemento;
                auto res = _eliminarRec(nodo->der, sucesor->elemento);
                nodo->der = res.first;
            }
        }
        NodoAVL<T>* balanceado = balancear(nodo);
        return { balanceado, true };
    }
    int _cantidad(NodoAVL<T>* nodo) {
        if (!nodo) return 0;
        return 1 + _cantidad(nodo->izq) + _cantidad(nodo->der);
    }
    int _altura(NodoAVL<T>* nodo) {
        return alturaNodo(nodo);
    }
    T _minimo(NodoAVL<T>* nodo) {
        NodoAVL<T>* n = nodoMinimo(nodo);
        if (!n) throw runtime_error("Arbol vacio");
        return n->elemento;
    }
    T _maximo(NodoAVL<T>* nodo) {
        NodoAVL<T>* actual = nodo;
        if (!actual) throw runtime_error("Arbol vacio");
        while (actual->der) actual = actual->der;
        return actual->elemento;
    }
    void _enOrden(NodoAVL<T>* nodo) {
        if (!nodo) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }
    void _preOrden(NodoAVL<T>* nodo) {
        if (!nodo) return;
        procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }
    void _postOrden(NodoAVL<T>* nodo) {
        if (!nodo) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        procesar(nodo->elemento);
    }
    T _sumarHojas(NodoAVL<T>* nodo) {
        if (!nodo) return (T)0;
        if (!nodo->izq && !nodo->der) return nodo->elemento;
        return _sumarHojas(nodo->izq) + _sumarHojas(nodo->der);
    }
    void _mostrarArbol(NodoAVL<T>* nodo, int nivel = 0) {
        if (!nodo) return;
        _mostrarArbol(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; ++i) cout << "  ";
        cout << nodo->elemento << " (h=" << nodo->altura << ")\n";
        _mostrarArbol(nodo->izq, nivel + 1);
    }
    void _liberar(NodoAVL<T>* nodo) {
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

    NodoAVL<T>* Obtener(T e) {
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

    void setComparador(Comp comp) { comparar = comp; }
};
