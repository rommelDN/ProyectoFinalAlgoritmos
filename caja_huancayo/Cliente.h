#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class Cliente {
private:
	T id_cliente;		//String
	T nombre;			//String
	T apellido;			//String
	T dni;				//String
	T correo;			//String
	T telefono;			//String
	
	string generarID() {
		static int contador = 1;
		return "CL" + "-" + to_string(contador++);
	}
public:
	Cliente(T n, T a, T d, T c, T t) : nombre(n), apellido(a), dni(d), correo(c), telefono(t) {
		id_cliente = generarID();
	}
	void mostrarInfo() const {
		cout << "ID: " << id_cliente
			<< " | DNI: " << dni
			<< " | Nombre: " << nombre << " " << apellido
			<< " | Depto: " << departamento
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

};