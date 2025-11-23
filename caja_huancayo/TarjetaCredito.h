#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <cmath>
#include "Tarjetas.h"

using namespace std;

template <typename T1, typename T2>
class TarjetaCredito : public Tarjetas<string> {
private:
	T1 id_credito;
	T2 linea_credito;
	T2 tasa_interes_mensual;
	T2 credito_utilizado;

	string generarID() {
		static int contador = 1;
		return "CRC-" + to_string(contador++);
	}

	// FUNCION RECURSIVA: Proyectar deuda con interes compuesto
	// Big O: O(n) donde n = numero de meses
	double proyectarDeudaRecursiva(double capital, int meses) {
		if (meses == 0) return capital;
		double interes = capital * (tasa_interes_mensual / 100.0);
		return proyectarDeudaRecursiva(capital + interes, meses - 1);
	}

public:
	// Constructor normal
	TarjetaCredito(T1 n_cuenta, T1 t, T1 f_a, T1 n_tarjeta, T1 f_emision, T1 f_vencimiento, T1 cvv, T2 linea_credito, T2 tasa_interes)
		: Tarjetas<string>(n_cuenta, t, f_a, n_tarjeta, f_emision, f_vencimiento, cvv), linea_credito(linea_credito), tasa_interes_mensual(tasa_interes), credito_utilizado(0.0) {
		id_credito = generarID();
	}

	// Constructor de copia
	TarjetaCredito(const TarjetaCredito& otra)
		: Tarjetas<string>(otra),
		id_credito(otra.id_credito),
		linea_credito(otra.linea_credito),
		tasa_interes_mensual(otra.tasa_interes_mensual),
		credito_utilizado(otra.credito_utilizado) {
	}

	// Operador de asignacion
	TarjetaCredito& operator=(const TarjetaCredito& otra) {
		if (this != &otra) {
			Tarjetas<string>::operator=(otra);
			id_credito = otra.id_credito;
			linea_credito = otra.linea_credito;
			tasa_interes_mensual = otra.tasa_interes_mensual;
			credito_utilizado = otra.credito_utilizado;
		}
		return *this;
	}

	// getters - Big O: O(1)
	T1 getIdCredito() const { return id_credito; }
	T2 getLineaCredito() const { return linea_credito; }
	T2 getTasaInteresMensual() const { return tasa_interes_mensual; }
	T2 getCreditoUtilizado() const { return credito_utilizado; }
	T2 getCreditoDisponible() const { return linea_credito - credito_utilizado; }

	// setters - Big O: O(1)
	void setLineaCredito(T2 linea_credito) { this->linea_credito = linea_credito; }
	void setTasaInteresMensual(T2 tasa_interes) { this->tasa_interes_mensual = tasa_interes; }

	// Big O: O(1) - Operaciones de impresion
	void mostrarInfo() const {
		Tarjetas<string>::mostrarInfo();
		cout << "ID Credito: " << id_credito
			<< " | Linea de Credito: $" << linea_credito
			<< " | Tasa de Interes Mensual: " << tasa_interes_mensual << "%"
			<< " | Credito Utilizado: $" << credito_utilizado
			<< " | Credito Disponible: $" << getCreditoDisponible() << endl;
	}

	// Big O: O(1) - Operaciones aritmeticas simples
	void usarCredito(double monto) {
		if (credito_utilizado + monto <= linea_credito) {
			credito_utilizado += monto;
			Transaccion<string, double> compra("COMPRA", monto, "Uso de credito");
			compra.completar();
			this->agrearTransaccion(compra);
			cout << "Se ha utilizado credito por un monto de $" << monto << ". Credito utilizado total: $" << credito_utilizado << endl;
		}
		else {
			cout << "No se puede utilizar el credito. Supera la linea de credito disponible." << endl;
		}
	}

	// Big O: O(1) - Operaciones aritmeticas simples
	void pagarCredito(double monto) {
		if (monto <= credito_utilizado) {
			credito_utilizado -= monto;
			Transaccion<string, double> pago("PAGO", monto, "Pago de credito");
			pago.completar();
			this->agrearTransaccion(pago);
			cout << "Se ha pagado un monto de $" << monto << " del credito utilizado. Credito restante: $" << credito_utilizado << endl;
		}
		else {
			cout << "El monto a pagar excede el credito utilizado. Pago no realizado." << endl;
		}
	}

	// Big O: O(1) - Calculo aritmetico simple
	void calcularInteresMensual() {
		T2 interes = credito_utilizado * (tasa_interes_mensual / 100);
		credito_utilizado += interes;
		cout << "Se ha calculado el interes mensual de $" << interes << ". Credito utilizado actualizado: $" << credito_utilizado << endl;
	}

	// Big O: O(1) - Suma simple
	void aumentarLineaCredito(T2 nuevo_limite) {
		linea_credito += nuevo_limite;
		cout << "La linea de credito ha sido aumentada en $" << nuevo_limite << ". Nueva linea de credito: $" << linea_credito << endl;
	}

	// METODO RECURSIVO PUBLICO: Proyectar deuda a N meses
	// Big O: O(n) donde n = numero de meses
	void proyectarDeuda(int meses) {
		if (credito_utilizado <= 0) {
			cout << "No hay deuda para proyectar." << endl;
			return;
		}
		cout << "\n=== PROYECCION DE DEUDA A " << meses << " MESES ===" << endl;
		cout << "Deuda actual: $" << credito_utilizado << endl;
		double deudaFinal = proyectarDeudaRecursiva(credito_utilizado, meses);
		cout << "Deuda proyectada: $" << deudaFinal << endl;
		cout << "Total intereses: $" << (deudaFinal - credito_utilizado) << endl;
	}

	// USO DE LAMBDA: Calcular estadisticas
	// Big O: O(1)
	void mostrarEstadisticas() {
		cout << "\n=== ESTADISTICAS ===" << endl;
		// Lambda para calcular porcentaje de uso
		auto porcentajeUso = [this]() -> double {
			return (credito_utilizado / linea_credito) * 100.0;
			};
		cout << "Linea de credito: $" << linea_credito << endl;
		cout << "Credito utilizado: $" << credito_utilizado << endl;
		cout << "Credito disponible: $" << getCreditoDisponible() << endl;
		cout << "Porcentaje de uso: " << porcentajeUso() << "%" << endl;
	}

	// Implementacion del metodo virtual puro
	// Big O: O(1)
	void realizarTransaccion(double monto) override {
		usarCredito(monto);
	}

};