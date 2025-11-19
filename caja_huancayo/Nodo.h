#pragma once
#include <iostream>
template <typename T>
class Nodo{
public:
	T dato;
	Nodo<T>* siguiente;
public:
	Nodo(T v, Nodo<T>*sig=NULL) :dato(v), siguiente(sig) {}
	T getDato() { return dato; }
	Nodo<T>* getSiguiente() { return siguiente; }
	void setSiguiente(Nodo<T>* sig) { siguiente = sig; }
	void setDato(T v) { dato = v; }

};