#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include "ListaEnlazada.h"
#include"Transaccion.h"
using namespace std;

template <typename T1, typename T2>
class Servicios {
private:
	T1 id_servicio;		//String
	T2 saldo;			//Double
	T1 num_cuenta;		//String
	T1 titular;			//String
	T1 fecha_apertura;	//String
	ListaEnlazada<Transaccion<string, double>>* historialTransacciones;


	string generarIDServicio() {
		static int contador = 1;
		return "SRV-" + to_string(contador++);
	}

public:
	Servicios(T1 n_cuenta, T1 t, T1 f_a) : num_cuenta(n_cuenta), titular(t), fecha_apertura(f_a), saldo(0.0) {
		id_servicio = generarIDServicio();
		historialTransacciones = new ListaEnlazada<Transaccion<string, double>>();
	}

	//getters
	T1 getIdServicio() const { return id_servicio; }
	T2 getSaldo() const { return saldo; }
	T1 getNumCuenta() const { return num_cuenta; }
	T1 getTitular() const { return titular; }
	T1 getFechaApertura() const { return fecha_apertura; }
	//setters
	void setSaldo(T2 s) { saldo = s; }
	void setTitular(T1 t) { titular = t; }
	void setNumCuenta(T1 n_cuenta) { num_cuenta = n_cuenta; }

	void agrearTransaccion(const Transaccion<string, double>& transaccion) {
		historialTransacciones->agregarFinal(transaccion);
		cout << "Transacci�n agregada al historial: " << transaccion.getTipo() << " - $" << transaccion.getMonto() << endl;
		if (transaccion.esCompletada()) actualizarSaldo(transaccion);

	}

	void actualizarSaldo(const Transaccion<string, double>& transaccion) {
		if (transaccion.esPendiente()) {
			cout << "La transaccion esta pendiente. No se actualiza el saldo." << endl;
			cout << "Completar o fallar la transaccion antes de actualizar el saldo." << endl;
			//esCompleta -> modifica mi estado PENDIENTA A COMPLETADA
			//esFallida -> modifica mi estado PENDIENTA A FALLIDA
		}
		if (transaccion.esCompletada()) {
			if (transaccion.esDeposito()) {
				this->saldo += transaccion.getMonto();
				cout << "Deposito exitoso. Nuevo saldo: " << this->saldo << endl;
			}
			else if (transaccion.esRetiro()) {
				this->saldo -= transaccion.getMonto();
				cout << "Retiro exitoso. Nuevo saldo: " << this->saldo << endl;
			}
		}
		if (transaccion.esFallida()) {
			cout << "La transaccion ha fallado. No se actualiza el saldo." << endl;
			cout << "Revisar posibles fallos en la transacion" << endl;
		}
	}

	void mostrarInfo() const {
		cout << "ID Servicio: " << id_servicio
			<< " | Num Cuenta: " << num_cuenta
			<< " | Titular: " << titular
			<< " | Fecha Apertura: " << fecha_apertura
			<< " | Saldo: $" << saldo << endl;
		//cout << "-> Historial de Transacciones: " << endl;
		//historialTransacciones->mostrarTodo();
	}

	static Servicios<string, double> obtenerXnumCuenta(ListaEnlazada<Servicios<string, double>>& lista, const string& num_cuenta) {
		if (lista.estaVacia()) {
			throw runtime_error("La lista esta vacia. No se puede obtener el elemento.");
		}
		Nodo<Servicios<string, double>>* actual = lista.getCabeza();
		while (actual != nullptr) {
			if (actual->getDato().getNumCuenta() == num_cuenta) {
				return actual->getDato();
			}
			actual = actual->getSiguiente();
		}
		throw runtime_error("No se encontro el servicio con el numero de cuenta proporcionado.");
	};

	void mostrarHistorialTransacciones() {
		cout << "\n=== HISTORIAL DE TRANSACCIONES ===\n";
		if (historialTransacciones == nullptr || historialTransacciones->estaVacia()) {
			cout << "No hay transacciones registradas.\n";
			return;
		}
		Nodo<Transaccion<string, double>>* actual = historialTransacciones->getCabeza();
		while (actual != nullptr) {
			auto& t = actual->getDatoref();
			t.mostrarInfo();
			actual = actual->siguiente;
		};
		cout << "\n=== FIN DEL HISTORIAL ===\n";
	}

	Servicios() = default;
};