#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include "Nodo.h"
using namespace std;

template <typename T>
class Pila {
private:
	Nodo<T>* tope;
	int tamanio;
public:
	Pila() : tope(NULL),tamanio(0){}
	bool estaVacia() const {
		return tope == nullptr;
	}
	~Pila() {
		while (!estaVacia()) {
			desapilar();
		}
	}
	void apilar(T e){
		Nodo<T>* nuevo = new Nodo<T>(e);
		nuevo->setSiguiente(tope);
		tope = nuevo;
		tamanio++;
	}
	T desapilar(){
		if(estaVacia()) {
			throw runtime_error("La pila esta vacia. No se puede desapilar.");
		}
		Nodo<T>* temp = tope;
		T dato = tope->getDato();
		tope = tope->getSiguiente();
		delete temp;
		tamanio--;
		return dato;
	}
	T getTope() {
		if(estaVacia()) {
			throw runtime_error("La pila esta vacia. No hay tope.");
		}
		return tope->getDato();
	}
	int getTamanio() const {
		return tamanio;
	}	
	void mostrarTodo(){
		if(estaVacia()) {
			cout << "La pila esta vacia." << endl;
			return;
		}
		cout << "* Contenido de la pila (" << tamanio << " elementos):" << endl;
		Nodo<T>* actual = tope;
		int contador = 1;
		while(actual != NULL) {
			cout << contador << ". " << actual->getDato() << endl;
			actual = actual->getSiguiente();
			contador++;
		}

	}

};