#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

template<class T>
class NodoBST {
public:
	T elemento;
	NodoBST* izq;
	NodoBST* der;

	NodoBST() : izq(nullptr), der(nullptr) {};
	NodoBST(T e) : elemento(e), izq(nullptr), der(nullptr) {};
};

template<class T>
class ArbolBB {
	typedef function<int(T, T)>Comp;
	NodoBST<T>* raiz;
	void(*procesar)(T);
	Comp comparar;

	function<int(const T&)> extractor;

private:
	bool _vacio() { return raiz == nullptr; };
	bool _insertar(NodoBST<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new NodoBST<T>(e);
			//nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0)return false;
			else if (r < 0)return _insertar(nodo->der, e);
			else return _insertar(nodo->izq, e);
		}
	}
	bool _buscar(NodoBST<T>* nodo, T e) {
		if (nodo == nullptr)return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0)return true;
			else if (r < 0)return _buscar(nodo->der, e);
			else return _buscar(nodo->izq, e);
		}
	}
	bool _eliminar(NodoBST<T>*& nodo, T e) {
		if (nodo == nullptr)return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r < 0) return _eliminar(nodo->der, e);
			else if (r > 0)return _eliminar(nodo->izq, e);
			else {
				if (nodo->izq == nullptr && nodo->der == nullptr) {
					delete nodo;
					nodo = nullptr;
					return true;
				}
				else if (nodo->izq == nullptr) {
					NodoBST<T>* temp = nodo;
					nodo = temp->der;
					delete temp;
					return true;
				}
				else if (nodo->der == nullptr) {
					NodoBST<T>* temp = nodo;
					nodo = temp->izq;
					delete temp;
					return true;
				}
				else {
					NodoBST<T>* aux = nodo->der;
					while (aux->izq != nullptr) {
						aux = aux->izq;
					}
					nodo->elemento = aux->elemento;
					return _eliminar(nodo->der, aux->elemento);
				}

			}
		}
	}
	NodoBST<T>* _obtener(NodoBST<T>* nodo, T e) {
		if (nodo == nullptr)return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0)return nodo;
			else if (r < 0)return _obtener(nodo->der, e);
			else return _obtener(nodo->izq, e);
		}

	}
	int _cantidad(NodoBST<T>* nodo) {
		if (nodo == nullptr)return 0;
		else {
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}
	}
	int _altura(NodoBST<T>* nodo) {
		if (nodo == nullptr)return 0;
		else {
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}
	T _minimo(NodoBST<T>* nodo) {
		if (nodo->izq == nullptr)nodo->elemento;
		else return _minimo(nodo->izq);
	}
	T _maximo(NodoBST<T>* nodo) {
		if (nodo->der == nullptr) nodo->elemento;
		else return _maximo(nodo->der);
	}
	void _enOrden(NodoBST<T>* nodo) {
		if (nodo == nullptr)return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}
	void _preOrden(NodoBST<T>* nodo) {
		if (nodo == nullptr)return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}
	void _postOrden(NodoBST<T>* nodo) {
		if (nodo == nullptr)return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}
	int _sumarSubArbolIzq(NodoBST<T>* nodo) {
		if (nodo == nullptr)return 0;
		return extractor(nodo->elemento)+ _sumarSubArbolIzq(nodo->izq)+ _sumarSubArbolIzq(nodo->der);
	}
	int _sumarHojas(NodoBST<T>* nodo) {
		if (nodo == nullptr)return 0;
		if (nodo->der == nullptr && nodo->der == nullptr) {
			return extractor(nodo->elemento);
		}
		return _sumarHojas(nodo->izq) + _sumarHojas(nodo->der);
	}
	void _mostrarArbol(NodoBST<T>*& nodo, int nivel = 0) {
		if (nodo == nullptr)return;
		_mostrarArbol(nodo->der, nivel + 1);
		for (int i = 0; i < nivel; i++) cout << "  ";
		cout << extractor(nodo->elemento) << endl;
		_mostrarArbol(nodo->izq, nivel + 1);
	}
public:
	ArbolBB(void(*otroPunteroFuncion)(T),Comp comparadorExterno, function<int(const T&)> extraExt) {
		this->procesar = otroPunteroFuncion;
		//this->comparar = [](T a, T b) {return a - b;};
		this->comparar = comparadorExterno;
		this->extractor = extraExt;
		raiz = nullptr;
	}
	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	NodoBST<T>* Obtener(T e) {
		return _obtener(raiz, e);
	}
	T Minimo() {
		return _minimo(raiz);
	}
	T Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
	int SumarHojas() {
		return _sumarHojas(raiz);
	}
	void mostrar() { return _mostrarArbol(raiz); }
};