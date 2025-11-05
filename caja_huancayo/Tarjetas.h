#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include "Servicios.h"

using namespace std;

template <typename T>
class Tarjetas : public Servicios<string, double> {
private:
	T id_tarjeta;
	T num_tarjeta;
	T fecha_emision;
	T fecha_vencimiento;
	T cvv;
	T estado; // Activa, Bloqueada, Cancelada
	string generarID() {
		static int contador = 1;
		return "TRJ-" + to_string(contador++);
	}
public:
	Tarjetas(T n_cuenta, T t, T f_a, T n_tarjeta, T f_emision, T f_vencimiento, T cvv)
		: Servicios<string, double>(n_cuenta, t, f_a), num_tarjeta(n_tarjeta), fecha_emision(f_emision), fecha_vencimiento(f_vencimiento), cvv(cvv) {
		id_tarjeta = generarID();
		estado = "Activa";
	}
	//getters
	T getIdTarjeta() { return id_tarjeta; }
	T getNumTarjeta() { return num_tarjeta; }
	T getFechaEmision() { return fecha_emision; }
	T getFechaVencimiento() { return fecha_vencimiento; }
	T getCvv() { return cvv; }
	T getEstado() { return estado; }
	//setters
	void setNumTarjeta(T n_tarjeta) { num_tarjeta = n_tarjeta; }
	void setFechaEmision(T f_emision) { fecha_emision = f_emision; }
	void setFechaVencimiento(T f_vencimiento) { fecha_vencimiento = f_vencimiento; }
	void setCvv(T cvv) { this->cvv = cvv; }
	void setEstado(T estado) { this->estado = estado; }

    double consultarSaldo() {
        return  Servicios<string, double>::getSaldo();
    }
	bool cancelarTarjeta()  {
		if (estado != "Cancelada") {
			estado = "Cancelada";
			cout << "La tarjeta ha sido cancelada." << endl;
			return true;
		}
		else {
			cout << "La tarjeta ya estaba cancelada." << endl;
			return false;
		}
	}

	void mostrarInfo() const {
		Servicios<string, double>::mostrarInfo();
		cout << "ID Tarjeta: " << id_tarjeta
			<< " | Num Tarjeta: " << num_tarjeta
			<< " | Fecha Emision: " << fecha_emision
			<< " | Fecha Vencimiento: " << fecha_vencimiento
			<< " | CVV: " << cvv
			<< " | Estado: " << estado << endl;
	}

	virtual void realizarTransaccion(double monto) = 0;

	void bloquearTarjeta() {
		if (estado == "Activa") {
			estado = "Bloqueada";
			cout << "La tarjeta ha sido bloqueada." << endl;
		}
		else if (estado == "Bloqueada") {
			cout << "La tarjeta ya esta bloqueada." << endl;
		}
		else {
			cout << "La tarjeta esta cancelada y no puede ser bloqueada." << endl;
		}
	}

	void desbloquearTarjeta() {
		if (estado == "Bloqueada") {
			estado = "Activa";
			cout << "La tarjeta ha sido desbloqueada." << endl;
		}
		else if (estado == "Activa") {
			cout << "La tarjeta ya esta activa." << endl;
		}
		else {
			cout << "La tarjeta esta cancelada y no puede ser desbloqueada." << endl;
		}
	}

	void revonarTarjeta(T new_fecha_vencimiento, T new_cvv) {
		if (estado != "Cancelada") {
			fecha_vencimiento = new_fecha_vencimiento;
			cvv = new_cvv;
			cout << "La tarjeta ha sido renovada. Nueva fecha de vencimiento: " << fecha_vencimiento << ", Nuevo CVV: " << cvv << endl;
		}
		else {
			cout << "La tarjeta esta cancelada y no puede ser renovada." << endl;
		}
	}
};