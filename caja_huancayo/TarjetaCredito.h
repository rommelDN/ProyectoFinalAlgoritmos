#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include "Tarjetas.h"
using namespace std;

template <typename T1, typename T2>
class TarjetaCredito : public Tarjetas<string> {
private:
	T1 id_credito;		//string
	T2 linea_credito;	//double
	T2 tasa_interes_mensual;
	T2 credito_utilizado; //double ; puede ser una lista o pila de movimientos de credito
	string generarID() {
		static int contador = 1;
		return "CRC-" + to_string(contador++);
	}
public:
	TarjetaCredito(T1 n_cuenta, T1 t, T1 f_a, T1 n_tarjeta, T1 f_emision, T1 f_vencimiento, T1 cvv, T2 linea_credito, T2 tasa_interes)
		: Tarjetas<string>(n_cuenta, t, f_a, n_tarjeta, f_emision, f_vencimiento, cvv), linea_credito(linea_credito), tasa_interes_mensual(tasa_interes), credito_utilizado(0.0) {
		id_credito = generarID();
	}
	//getters
	T1 getIdCredito() { return id_credito; }
	T2 getLineaCredito() { return linea_credito; }
	T2 getTasaInteresMensual() { return tasa_interes_mensual; }
	T2 getCreditoUtilizado() { return credito_utilizado; }
	//setters
	void setLineaCredito(T2 linea_credito) { this->linea_credito = linea_credito; }
	void setTasaInteresMensual(T2 tasa_interes) { this->tasa_interes_mensual = tasa_interes; }
	void mostrarInfo() const {
		Tarjetas<string>::mostrarInfo();
		cout << "ID Credito: " << id_credito
			<< " | Linea de Credito: $" << linea_credito
			<< " | Tasa de Interes Mensual: " << tasa_interes_mensual << "%"
			<< " | Credito Utilizado: $" << credito_utilizado << endl;
	}
	void usarCredito(double monto) {
		if (credito_utilizado + monto <= linea_credito) {
			credito_utilizado += monto;
			cout << "Se ha utilizado credito por un monto de $" << monto << ". Credito utilizado total: $" << credito_utilizado << endl;
		}
		else {
			cout << "No se puede utilizar el credito. Supera la linea de credito disponible." << endl;
		}
	}
	void pagarCredito(double monto) {
		if (monto <= credito_utilizado) {
			credito_utilizado -= monto;
			cout << "Se ha pagado un monto de $" << monto << " del credito utilizado. Credito restante: $" << credito_utilizado << endl;
		}
		else {
			cout << "El monto a pagar excede el credito utilizado. Pago no realizado." << endl;
		}
	}
	void calcularInteresMensual() {
		T2 interes = credito_utilizado * (tasa_interes_mensual / 100);
		credito_utilizado += interes;
		cout << "Se ha calculado el interes mensual de $" << interes << ". Credito utilizado actualizado: $" << credito_utilizado << endl;
	}
	void aumentarLineaCredito(T2 nuevo_limite) {
		linea_credito += nuevo_limite;
		cout << "La linea de credito ha sido aumentada en $" << nuevo_limite << ". Nueva linea de credito: $" << linea_credito << endl;
	}

};