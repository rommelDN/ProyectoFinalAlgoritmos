#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <vector>
#include <cmath>
#include "Servicios.h"
#include "Pila.h"

using namespace std;

template <typename T>
class Tarjetas : public Servicios<string, double> {
private:
	T id_tarjeta;
	T num_tarjeta;
	T fecha_emision;
	T fecha_vencimiento;
	T cvv;
	T estado;

	// ESTRUCTURA DE DATOS: Pila para movimientos pendientes
	Pila<Transaccion<string, double>>* movimientosPendientes;

	string generarID() {
		static int contador = 1;
		return "TRJ-" + to_string(contador++);
	}

	// FUNCION RECURSIVA: Calcular dias hasta vencimiento
	// Big O: O(n) donde n = dias entre fechas
	int calcularDiasRecursivo(int dia_actual, int mes_actual, int anio_actual,
		int dia_venc, int mes_venc, int anio_venc) {
		// Caso base: misma fecha
		if (dia_actual == dia_venc && mes_actual == mes_venc && anio_actual == anio_venc) {
			return 0;
		}
		// Si ya paso la fecha
		if (anio_actual > anio_venc ||
			(anio_actual == anio_venc && mes_actual > mes_venc) ||
			(anio_actual == anio_venc && mes_actual == mes_venc && dia_actual > dia_venc)) {
			return -1;
		}
		// Avanzar un dia
		dia_actual++;
		if (dia_actual > 30) {
			dia_actual = 1;
			mes_actual++;
			if (mes_actual > 12) {
				mes_actual = 1;
				anio_actual++;
			}
		}
		return 1 + calcularDiasRecursivo(dia_actual, mes_actual, anio_actual,
			dia_venc, mes_venc, anio_venc);
	}

public:
	// Constructor normal
	Tarjetas(T n_cuenta, T t, T f_a, T n_tarjeta, T f_emision, T f_vencimiento, T cvv)
		: Servicios<string, double>(n_cuenta, t, f_a), num_tarjeta(n_tarjeta), fecha_emision(f_emision), fecha_vencimiento(f_vencimiento), cvv(cvv) {
		id_tarjeta = generarID();
		estado = "Activa";
		movimientosPendientes = new Pila<Transaccion<string, double>>();
	}

	// Constructor de copia (DEEP COPY) - RULE OF THREE
	Tarjetas(const Tarjetas& otra)
		: Servicios<string, double>(otra.getNumCuenta(), otra.getTitular(), otra.getFechaApertura()),
		id_tarjeta(otra.id_tarjeta),
		num_tarjeta(otra.num_tarjeta),
		fecha_emision(otra.fecha_emision),
		fecha_vencimiento(otra.fecha_vencimiento),
		cvv(otra.cvv),
		estado(otra.estado) {
		// Crear nueva Pila vacia (deep copy)
		movimientosPendientes = new Pila<Transaccion<string, double>>();
	}

	// Operador de asignacion - RULE OF THREE
	Tarjetas& operator=(const Tarjetas& otra) {
		if (this != &otra) {
			// Copiar datos base
			Servicios<string, double>::operator=(otra);
			id_tarjeta = otra.id_tarjeta;
			num_tarjeta = otra.num_tarjeta;
			fecha_emision = otra.fecha_emision;
			fecha_vencimiento = otra.fecha_vencimiento;
			cvv = otra.cvv;
			estado = otra.estado;

			// Borrar pila antigua
			delete movimientosPendientes;
			// Crear nueva pila vacia
			movimientosPendientes = new Pila<Transaccion<string, double>>();
		}
		return *this;
	}

	// Destructor - RULE OF THREE
	~Tarjetas() {
		delete movimientosPendientes;
	}

	// getters - Big O: O(1)
	T getIdTarjeta() const { return id_tarjeta; }
	T getNumTarjeta() const { return num_tarjeta; }
	T getFechaEmision() const { return fecha_emision; }
	T getFechaVencimiento() const { return fecha_vencimiento; }
	T getCvv() const { return cvv; }
	T getEstado() const { return estado; }

	// setters - Big O: O(1)
	void setNumTarjeta(T n_tarjeta) { num_tarjeta = n_tarjeta; }
	void setFechaEmision(T f_emision) { fecha_emision = f_emision; }
	void setFechaVencimiento(T f_vencimiento) { fecha_vencimiento = f_vencimiento; }
	void setCvv(T cvv) { this->cvv = cvv; }
	void setEstado(T estado) { this->estado = estado; }

	// Big O: O(1) - Acceso directo al saldo heredado
	double consultarSaldo() {
		return  Servicios<string, double>::getSaldo();
	}

	// Big O: O(1) - Comparacion y asignacion
	bool cancelarTarjeta() {
		if (estado != "Cancelada") {
			estado = "Cancelada";
			cout << "La tarjeta " << num_tarjeta << " ha sido cancelada." << endl;
			return true;
		}
		else {
			cout << "La tarjeta ya estaba cancelada." << endl;
			return false;
		}
	}

	// Big O: O(1) - Operaciones de impresion
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

	// Big O: O(1) - Operacion condicional simple
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

	// Big O: O(1) - Operacion condicional simple
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

	// Big O: O(1) - Asignacion de dos atributos
	void renovarTarjeta(T new_fecha_vencimiento, T new_cvv) {
		if (estado != "Cancelada") {
			fecha_vencimiento = new_fecha_vencimiento;
			cvv = new_cvv;
			cout << "La tarjeta ha sido renovada. Nueva fecha de vencimiento: " << fecha_vencimiento << ", Nuevo CVV: " << cvv << endl;
		}
		else {
			cout << "La tarjeta esta cancelada y no puede ser renovada." << endl;
		}
	}

	// METODO RECURSIVO PUBLICO: Calcular dias hasta vencimiento
	// Big O: O(n) donde n = numero de dias
	int diasHastaVencimiento(string fecha_actual) {
		// Formato esperado: dd/mm/yyyy
		int dia_act = stoi(fecha_actual.substr(0, 2));
		int mes_act = stoi(fecha_actual.substr(3, 2));
		int anio_act = stoi(fecha_actual.substr(6, 4));

		int dia_venc = stoi(fecha_vencimiento.substr(0, 2));
		int mes_venc = stoi(fecha_vencimiento.substr(3, 2));
		int anio_venc = stoi(fecha_vencimiento.substr(6, 4));

		int dias = calcularDiasRecursivo(dia_act, mes_act, anio_act, dia_venc, mes_venc, anio_venc);

		if (dias < 0) {
			cout << "ALERTA: La tarjeta ya vencio." << endl;
		}
		else if (dias <= 30) {
			cout << "ALERTA: La tarjeta vence en " << dias << " dias." << endl;
		}

		return dias;
	}

	// Agregar movimiento pendiente
	// Big O: O(1) - Operacion apilar
	void agregarMovimientoPendiente(const Transaccion<string, double>& trans) {
		movimientosPendientes->apilar(trans);
		cout << "Movimiento agregado a pendientes." << endl;
	}

	// Procesar movimientos pendientes
	// Big O: O(n) donde n = numero de movimientos
	void procesarMovimientosPendientes() {
		if (movimientosPendientes->estaVacia()) {
			cout << "No hay movimientos pendientes." << endl;
			return;
		}
		while (!movimientosPendientes->estaVacia()) {
			Transaccion<string, double> trans = movimientosPendientes->desapilar();
			trans.completar();
			this->agrearTransaccion(trans);
		}
		cout << "Movimientos procesados." << endl;
	}

	// USO DE LAMBDA: Mostrar movimientos pendientes
	// Big O: O(n) donde n = tamanio de la pila
	void mostrarMovimientosPendientes() {
		if (movimientosPendientes->estaVacia()) {
			cout << "No hay movimientos pendientes." << endl;
			return;
		}
		cout << "\n=== MOVIMIENTOS PENDIENTES ===" << endl;
		// Lambda para imprimir cada transaccion
		movimientosPendientes->mostrar([](const Transaccion<string, double>& t) {
			t.mostrarInfo();
			});
	}
};