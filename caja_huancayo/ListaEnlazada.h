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
class ListaEnlazada {
private:
	Nodo<T>* cabeza;
	int tamanio;
public:
	ListaEnlazada() : cabeza(NULL), tamanio(0) {}
	~ListaEnlazada() {
		Nodo<T>* actual = cabeza;
		while (actual != NULL) {
			Nodo<T>* siguiente = actual->getSiguiente();
			delete actual;
			actual = siguiente;
		}
	}
	void agregarFinal(T e) {
		Nodo<T>* nuevo = new Nodo<T>(e);
		if (cabeza == NULL) {
			cabeza = nuevo;
		}
		else {
			Nodo<T>* actual = cabeza;
			while (actual->getSiguiente() != NULL)
			{
				actual = actual->getSiguiente();
			}
			actual->setSiguiente(nuevo);
		}
		tamanio++;
	}
	Nodo<T>* getCabeza() {
		return cabeza;
	}	
	int getTamanio() {
		return tamanio;
	}
	bool estaVacia() {
		return cabeza == NULL;
	}
	
	void mostrarTodo() {
		if(estaVacia()) {
			cout << "La lista esta vacia." << endl;
			return;
		}
		Nodo<T>* actual = cabeza;
		int contador = 1;
		while(actual != NULL) {
			cout << contador << ". ";
			actual->getDato().mostrarInfo();
			actual = actual->getSiguiente();
			contador++;
		}
	}

	
	
};

