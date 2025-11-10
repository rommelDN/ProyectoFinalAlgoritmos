#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename T1, typename T2>
class Transaccion {
private:
	T1 id_transaccion;	//String
	T1 tipo;			//String : "DEPOSITO", "RETIRO",
	T2 monto;			//Double
	T1 descripcion;		//String
	T1 estado;			//String:  "PENDIENTE", "COMPLETADA", "FALLIDA"

	string generarID() {
		static int contador = 1;
		return "TXN -" + to_string(contador++);
	}
public:
	Transaccion(T1 t, T2 m, T1 d) : tipo(t), monto(m), descripcion(d){
		id_transaccion = generarID();
		estado = "PENDIENTE";
	}
	bool completar(){
		if(estado == "PENDIENTE") {
			estado = "COMPLETADA";
			return true;
		}
		return false;
	}
	bool fallar(){
		if(estado == "PENDIENTE") {
			estado = "FALLIDA";
			return true;
		}
		return false;
	}
	bool esCompletada() const {
		return estado == "COMPLETADA";
	}
	bool esFallida() const {
		return estado == "FALLIDA";
	}
	bool esPendiente() const {
		return estado == "PENDIENTE";
	}
	bool esDeposito() const {
		return tipo == "DEPOSITO";
	}
	bool esRetiro() const {
		return tipo == "RETIRO";
	}
	T2 getMonto() const {
		return monto;
	}
	T1 getTipo() const {
		return tipo;
	}
	T1 getDescripcion() const {
		return descripcion;
	}
	T1 getEstado() const {
		return estado;
	}
	void mostrarInfo() const {
		cout << "ID: " << id_transaccion << endl;
		cout << "Tipo: " << tipo << endl;
		cout << "Monto: $" << monto << endl;
		cout << "Descripción: " << descripcion << endl;
		cout << "Estado: " << estado << endl;
		cout << "=================================" << endl;
	}
};