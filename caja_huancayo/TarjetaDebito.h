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

	// ========================================
	// HITO 2: METODOS MEJORADOS CON ARBOL Y GRAFO
	// ========================================

	// Transferir dinero a otra tarjeta (usa el grafo)
	// Big O: O(log n)
	void transferirDinero(string tarjetaDestino, double monto) {
		if (monto > this->getSaldo()) {
			cout << "ERROR: Saldo insuficiente para la transferencia" << endl;
			return;
		}
		if (retirado_hoy + monto > limite_diario_retiro) {
			cout << "ERROR: Excede limite diario. Disponible: $" << getLimiteDisponibleHoy() << endl;
			return;
		}

		// Realizar el retiro
		retirar(monto);

		// Registrar en el grafo
		time_t now = time(0);
		char buffer[26];
#ifdef _WIN32
		ctime_s(buffer, sizeof(buffer), &now);
#else
		ctime_r(&now, buffer);
#endif
		string fecha = buffer;
		fecha = fecha.substr(0, fecha.length() - 1); // Quitar \n
		this->registrarTransferencia(tarjetaDestino, monto, fecha);

		cout << "Transferencia completada exitosamente" << endl;
	}

	// Analizar patrones de retiro usando grafo
	// Big O: O(V + E)
	void analizarPatronesRetiro() {
		cout << "\n=== ANALISIS DE PATRONES - TARJETA DEBITO " << this->getNumTarjeta() << " ===" << endl;

		// Mostrar transferencias realizadas
		this->mostrarMisTransferencias();

		// Calcular total transferido
		double totalTransferido = this->calcularTotalEnviado();
		if (totalTransferido > 0) {
			cout << "\nTotal transferido: $" << totalTransferido << endl;

			// Lambda para calcular promedio
			auto calcularPromedio = [totalTransferido](int numTransferencias) -> double {
				return numTransferencias > 0 ? totalTransferido / numTransferencias : 0;
				};

			// Aquí podrías contar las transferencias desde el grafo
			cout << "Monto promedio por transferencia: (ver grafo completo)" << endl;

			// Mostrar red de conexiones
			cout << "\nRed de transferencias desde esta tarjeta:" << endl;
			this->recorridoBFS(this->getNumTarjeta());
		}
		else {
			cout << "No se han realizado transferencias desde esta tarjeta" << endl;
		}
	}

	// Registrar tarjeta en árbol AVL
	// Big O: O(log n)
	void registrarEnArbol() {
		this->insertarEnArbol();
		cout << "Tarjeta de debito registrada en el arbol AVL" << endl;
	}

	// Verificar conectividad con otra tarjeta
	// Big O: O(V + E)
	void verificarConexionCon(string otraTarjeta) {
		cout << "\n=== VERIFICAR CONEXION ===" << endl;
		cout << "Desde: " << this->getNumTarjeta() << endl;
		cout << "Hacia: " << otraTarjeta << endl;

		if (this->existeCamino(this->getNumTarjeta(), otraTarjeta)) {
			cout << "EXISTE una ruta de transferencias entre estas tarjetas" << endl;
		}
		else {
			cout << "NO EXISTE conexion directa o indirecta" << endl;
		}
	}

	// Lambda avanzada: Simular retiros programados
	// Big O: O(k)
	void simularRetirosSemanales(int numSemanas) {
		cout << "\n=== SIMULACION DE RETIROS SEMANALES ===" << endl;

		// Lambda que calcula distribución óptima
		auto distribucionOptima = [this](int semanas) -> double {
			double limiteTotal = limite_diario_retiro * 7 * semanas; // 7 días por semana
			double retiroPorSemana = limiteTotal / semanas;
			return retiroPorSemana;
			};

		// Lambda para verificar si es factible
		auto esFactible = [this](double retiroPorSemana) -> bool {
			double retiroDiario = retiroPorSemana / 7;
			return retiroDiario <= limite_diario_retiro;
			};

		double retiroSemanal = distribucionOptima(numSemanas);

		cout << "Numero de semanas: " << numSemanas << endl;
		cout << "Retiro semanal optimo: $" << retiroSemanal << endl;
		cout << "Retiro diario promedio: $" << (retiroSemanal / 7) << endl;

		if (esFactible(retiroSemanal)) {
			cout << "Plan FACTIBLE dentro de limites diarios" << endl;
		}
		else {
			cout << "Plan NO FACTIBLE - excede limite diario" << endl;
		}
	}

	// Explorar red completa de transferencias usando DFS recursivo
	// Big O: O(V + E)
	void explorarRedCompleta() {
		cout << "\n=== EXPLORACION COMPLETA DE RED (DFS RECURSIVO) ===" << endl;
		cout << "Iniciando desde tarjeta: " << this->getNumTarjeta() << endl;
		this->recorridoDFS(this->getNumTarjeta());
	}
};
