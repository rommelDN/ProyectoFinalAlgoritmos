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
class Cola {
private:
	Nodo<T>* frente;
	Nodo<T>* final;
	int tamanio;
public:
	Cola() : frente(NULL), final(NULL), tamanio(0) {}
	bool estaVacia() const {
		return frente == nullptr;
	}
	~Cola() {
		while (!estaVacia()) {
			desencolar();
		}
	}
	void encolar(T e){
		Nodo<T>* nuevo = new Nodo<T>(e);
		if (final == NULL) {
			frente = final = nuevo;
		}
		else {
			final->setSiguiente(nuevo);
			final = nuevo;
		}
		tamanio++;
	}
	T desencolar(){
		if(estaVacia()) {
			throw runtime_error("La cola esta vacia. No se puede desencolar.");
		}
		Nodo<T>* temp = frente;
		T dato = frente->getDato();
		frente = frente->getSiguiente();
		if(frente == nullptr){
			final = nullptr;
		}
		delete temp;
		tamanio--;
		return dato;
	}
	T getFrente() {
		if(estaVacia()) {
			throw runtime_error("La cola esta vacia. No hay frente.");
		}
		return frente->getDato();
	}
	int getTamanio() const {
		return tamanio;
	}	
	void mostrarTodo(){
		if(estaVacia()) {
			cout << "La cola esta vacia." << endl;
			return;
		}
		cout << "Contenido de la cola (" << tamanio << " elementos):" << endl;
		Nodo<T>* actual = frente;
		int posicion = 1;
		while (actual != NULL)
		{
			cout << posicion << ". " << actual->getDato() << endl;
			actual = actual->getSiguiente();
			posicion++;
		}
		
	}
	T& getFrenteRef() {
		if (estaVacia()) {
			throw std::runtime_error("ERROR: Cola vacía");
		}
		return frente->dato; // Devuelve referencia al dato original
	}
	void mostrar(function<void(const T&)> printElemento) const {
		Nodo<T>* actual = frente;
		while (actual != nullptr) {
			printElemento(actual->getDato());
			actual = actual->getSiguiente();
		}
	}

};