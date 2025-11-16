#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include "ListaEnlazada.h"
template <typename T>
class Cliente {
private:
	T id_cliente;		//String
	T nombre;			//String
	T apellido;			//String
	T dni ;				//String
	T correo;			//String
	T telefono;			//String
	
	string generarID() {
		static int contador = 1;
		return "CL-" + to_string(contador++);
	}
public:
	Cliente(T n, T a, T d, T c, T t) : nombre(n), apellido(a), dni(d), correo(c), telefono(t) {
		id_cliente = generarID();
	}
	void mostrarInfo() const {
		cout << "ID: " << id_cliente
			<< " | DNI: " << dni
			<< " | Nombre: " << nombre << " " << apellido
			<< " | Correo: " << correo
			<< " | Tel: " << telefono << endl;
	}

	//getters
	T getID() const { return id_cliente; }
	T getNombre() const { return nombre; }
	T getApellido() const { return apellido; }
	T getDNI() const { return dni; }
	T getCorreo() const { return correo; }
	T getTelefono() const { return telefono; }
	//setters
	void setNombre(T n) { nombre = n; }
	void setApellido(T a) { apellido = a; }
	void setDNI(T d) { dni = d; }
	void setCorreo(T c) { correo = c; }
	void setTelefono(T t) { telefono = t; }

    // Solución: obtenerXdni debe recibir una referencia a la lista enlazada y retornar un Cliente<string>.
    // Además, el tipo de retorno debe coincidir con el tipo de función.
    static Cliente<string> obtenerXdni(ListaEnlazada<Cliente<string>>& lista, const string& dni) {
        if (lista.estaVacia()) {
            throw runtime_error("La lista esta vacia. No se puede obtener el elemento.");
        }
        Nodo<Cliente<string>>* actual = lista.getCabeza();
        while (actual != nullptr) {
            if (actual->getDato().getDNI() == dni) {
                return actual->getDato();
            }
            actual = actual->getSiguiente();
        }
        throw runtime_error("No se encontró el cliente con el DNI proporcionado.");
    }

	void mostrar() {
		cout << "Cliente[ID: " << id_cliente << ", Nombre: " << nombre << ", Apellido: " << apellido << ", DNI: " << dni << ", Correo: " << correo << ", Telefono: " << telefono << "]" << endl;
	};

	// Sobrecarga del operador << para poder imprimir
	friend ostream& operator<<(ostream& os, const Cliente& e) {
		os << e.getNombre() << " " << e.getApellido() << "("<<"DNI: "<<e.getDNI()<<" | Correo: "<<e.getCorreo()<<" | Telefono: "<<e.getTelefono() << ")";
		return os;
	}

	Cliente() = default;
};


