#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <vector>
#include "Tarjetas.h"
using namespace std;

template <typename T1, typename T2>
class TarjetaDebito : public Tarjetas<string> {
private:
	T1 id_debito;
	T2 limite_diario_retiro;
	T2 retirado_hoy;

	string generarID() {
		static int contador = 1;
		return "DBT-" + to_string(contador++);
	}

	// FUNCION RECURSIVA: Validar retiros consecutivos
	// Big O: O(n) donde n = numero de retiros
	bool validarRetirosRecursivo(vector<double> retiros, int index, double acumulado) {
		if (index >= retiros.size()) return acumulado <= limite_diario_retiro;
		double nuevoAcum = acumulado + retiros[index];
		if (nuevoAcum > limite_diario_retiro) return false;
		return validarRetirosRecursivo(retiros, index + 1, nuevoAcum);
	}

public:
	// Constructor normal
	TarjetaDebito(T1 n_cuenta, T1 t, T1 f_a, T1 n_tarjeta, T1 f_emision, T1 f_vencimiento, T1 cvv, T2 limite_retiro)
		: Tarjetas<string>(n_cuenta, t, f_a, n_tarjeta, f_emision, f_vencimiento, cvv), limite_diario_retiro(limite_retiro), retirado_hoy(0.0) {
		id_debito = generarID();
	}

	// Constructor de copia
	TarjetaDebito(const TarjetaDebito& otra)
		: Tarjetas<string>(otra),
		id_debito(otra.id_debito),
		limite_diario_retiro(otra.limite_diario_retiro),
		retirado_hoy(otra.retirado_hoy) {
	}

	// Operador de asignacion
	TarjetaDebito& operator=(const TarjetaDebito& otra) {
		if (this != &otra) {
			Tarjetas<string>::operator=(otra);
			id_debito = otra.id_debito;
			limite_diario_retiro = otra.limite_diario_retiro;
			retirado_hoy = otra.retirado_hoy;
		}
		return *this;
	}

	// getters - Big O: O(1)
	T1 getIdDebito() const { return id_debito; }
	T2 getLimiteDiarioRetiro() const { return limite_diario_retiro; }
	T2 getRetiradoHoy() const { return retirado_hoy; }
	T2 getLimiteDisponibleHoy() const { return limite_diario_retiro - retirado_hoy; }

	// setters - Big O: O(1)
	void setLimiteDiarioRetiro(T2 limite_retiro) { this->limite_diario_retiro = limite_retiro; }

	// Big O: O(1) - Operaciones de impresion
	void mostrarInfo() const {
		Tarjetas<string>::mostrarInfo();
		cout << "ID Debito: " << id_debito
			<< " | Limite Diario Retiro: $" << limite_diario_retiro
			<< " | Retirado Hoy: $" << retirado_hoy
			<< " | Disponible Hoy: $" << getLimiteDisponibleHoy() << endl;
	}

	// Big O: O(1) - Validaciones y actualizacion
	void retirar(double monto) {
		if (this->getEstado() != "Activa") {
			cout << "ERROR: La tarjeta no esta activa." << endl;
			return;
		}
		if (retirado_hoy + monto > limite_diario_retiro) {
			cout << "ERROR: Excede limite diario. Disponible: $" << getLimiteDisponibleHoy() << endl;
			return;
		}
		if (monto > this->getSaldo()) {
			cout << "ERROR: Saldo insuficiente." << endl;
			return;
		}
		retirado_hoy += monto;
		Transaccion<string, double> retiro("RETIRO", monto, "Retiro con tarjeta");
		retiro.completar();
		this->agrearTransaccion(retiro);
		cout << "Retiro exitoso de $" << monto << ". Saldo: $" << this->getSaldo() << endl;
	}

	// Big O: O(1) - Actualizacion simple
	void depositar(double monto) {
		if (monto <= 0) {
			cout << "ERROR: Monto debe ser mayor a 0." << endl;
			return;
		}
		Transaccion<string, double> deposito("DEPOSITO", monto, "Deposito");
		deposito.completar();
		this->agrearTransaccion(deposito);
		cout << "Deposito exitoso de $" << monto << endl;
	}

	// Big O: O(1) - Acceso directo
	void consultarSaldoDetallado() const {
		cout << "\n=== SALDO ===" << endl;
		cout << "Saldo: $" << this->getSaldo() << endl;
		cout << "Limite diario: $" << limite_diario_retiro << endl;
		cout << "Disponible hoy: $" << getLimiteDisponibleHoy() << endl;
	}

	// Big O: O(n) - Recorre historial
	void listarMovimientos() const {
		cout << "\n=== MOVIMIENTOS ===" << endl;
		this->mostrarHistorialTransacciones();
	}

	// Big O: O(1) - Reseteo simple
	void resetearLimiteDiario() {
		retirado_hoy = 0.0;
		cout << "Limite diario restablecido." << endl;
	}

	// METODO RECURSIVO PUBLICO: Validar retiros planeados
	// Big O: O(n) donde n = numero de retiros
	bool validarRetirosDelDia(vector<double> retiros) {
		if (retiros.empty()) return true;
		cout << "\n=== VALIDANDO RETIROS ===" << endl;
		return validarRetirosRecursivo(retiros, 0, retirado_hoy);
	}

	// USO DE LAMBDA: Mostrar estadisticas
	// Big O: O(1)
	void mostrarEstadisticas() {
		cout << "\n=== ESTADISTICAS ===" << endl;
		// Lambda para porcentaje
		auto porcentaje = [this]() -> double {
			return (retirado_hoy / limite_diario_retiro) * 100.0;
			};
		cout << "Saldo: $" << this->getSaldo() << endl;
		cout << "Limite diario: $" << limite_diario_retiro << endl;
		cout << "Retirado hoy: $" << retirado_hoy << endl;
		cout << "Uso del limite: " << porcentaje() << "%" << endl;
	}

	// Implementacion del metodo virtual puro
	// Big O: O(1)
	void realizarTransaccion(double monto) override {
		retirar(monto);
	}
};