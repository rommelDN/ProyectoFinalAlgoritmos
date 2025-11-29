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
#include <map>
#include <set>
#include <queue>
#include "Servicios.h"
#include "Pila.h"
#include "ArbolBinarioVL.h"  // Usando AVL (mejor que BST)

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

	// ========================================
	// HITO 2: PRIMER ARBOL AVL - POR NUMERO DE TARJETA
	// ========================================
	static ArbolAVL<string>* arbolTarjetasPorNumero;
	static bool arbol1Inicializado;

	// ========================================
	// HITO 2: SEGUNDO ARBOL AVL - POR SALDO/CREDITO
	// ========================================
	struct TarjetaPorMonto {
		double monto;
		string numTarjeta;

		TarjetaPorMonto() : monto(0), numTarjeta("") {}
		TarjetaPorMonto(double m, string n) : monto(m), numTarjeta(n) {}

		// Operadores para el AVL
		bool operator<(const TarjetaPorMonto& otro) const { return monto < otro.monto; }
		bool operator>(const TarjetaPorMonto& otro) const { return monto > otro.monto; }
		bool operator==(const TarjetaPorMonto& otro) const { return monto == otro.monto; }

		int operator-(const TarjetaPorMonto& otro) const {
			if (monto < otro.monto) return -1;
			if (monto > otro.monto) return 1;
			return 0;
		}

		friend ostream& operator<<(ostream& os, const TarjetaPorMonto& t) {
			os << t.numTarjeta << "($" << t.monto << ")";
			return os;
		}
	};

	static ArbolAVL<TarjetaPorMonto>* arbolTarjetasPorMonto;
	static bool arbol2Inicializado;

	// ========================================
	// HITO 2: GRAFO DE TRANSFERENCIAS (STATIC)
	// ========================================
	struct Transferencia {
		string origen;
		string destino;
		double monto;
		string fecha;
	};
	static map<string, vector<Transferencia>>* grafoTransferencias;
	static bool grafoInicializado;

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

	// ========================================
	// HITO 2: FUNCIONES AUXILIARES RECURSIVAS PARA GRAFO
	// ========================================

	// Recorrido DFS recursivo
	// Big O: O(V + E)
	static void recorridoDFSRecursivo(string nodo, set<string>& visitados) {
		visitados.insert(nodo);
		cout << nodo << " ";

		if (grafoTransferencias != nullptr) {
			auto it = grafoTransferencias->find(nodo);
			if (it != grafoTransferencias->end()) {
				for (const auto& trans : it->second) {
					if (visitados.find(trans.destino) == visitados.end()) {
						recorridoDFSRecursivo(trans.destino, visitados);
					}
				}
			}
		}
	}

public:
	// Constructor normal
	Tarjetas(T n_cuenta, T t, T f_a, T n_tarjeta, T f_emision, T f_vencimiento, T cvv)
		: Servicios<string, double>(n_cuenta, t, f_a), num_tarjeta(n_tarjeta), fecha_emision(f_emision), fecha_vencimiento(f_vencimiento), cvv(cvv) {
		id_tarjeta = generarID();
		estado = "Activa";
		movimientosPendientes = new Pila<Transaccion<string, double>>();

		// Inicializar estructuras estáticas si es necesario
		if (!arbol1Inicializado) {
			arbolTarjetasPorNumero = new ArbolAVL<string>([](string s) { cout << s << " "; });
			arbol1Inicializado = true;
		}
		if (!arbol2Inicializado) {
			arbolTarjetasPorMonto = new ArbolAVL<TarjetaPorMonto>([](TarjetaPorMonto t) {
				cout << t << " ";
				});
			arbol2Inicializado = true;
		}
		if (!grafoInicializado) {
			grafoTransferencias = new map<string, vector<Transferencia>>();
			grafoInicializado = true;
		}
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

	// ========================================
	// HITO 2: METODOS DEL PRIMER ARBOL AVL (POR NUMERO)
	// ========================================

	// Insertar tarjeta en el primer árbol AVL (por número)
	// Big O: O(log n) garantizado (AVL auto-balancea)
	void insertarEnArbolPorNumero() {
		if (arbolTarjetasPorNumero != nullptr) {
			arbolTarjetasPorNumero->insertar(num_tarjeta);
			cout << "Tarjeta " << num_tarjeta << " insertada en ARBOL 1 (por numero)" << endl;
		}
	}

	// Buscar tarjeta en el primer árbol
	// Big O: O(log n)
	static bool buscarEnArbolPorNumero(string numTarjeta) {
		if (arbolTarjetasPorNumero != nullptr) {
			return arbolTarjetasPorNumero->Buscar(numTarjeta);
		}
		return false;
	}

	// Mostrar todas las tarjetas ordenadas por número (recorrido InOrden)
	// Big O: O(n)
	static void mostrarArbol1Ordenado() {
		if (arbolTarjetasPorNumero != nullptr) {
			cout << "\n=== ARBOL 1: TARJETAS ORDENADAS POR NUMERO ===" << endl;
			cout << "Cantidad: " << arbolTarjetasPorNumero->cantidad()
				<< " | Altura: " << arbolTarjetasPorNumero->altura() << endl;
			arbolTarjetasPorNumero->enOrden();
			cout << endl;
		}
	}

	// Mostrar estructura del primer árbol
	// Big O: O(n)
	static void mostrarEstructuraArbol1() {
		if (arbolTarjetasPorNumero != nullptr) {
			cout << "\n=== ESTRUCTURA DEL ARBOL 1 (POR NUMERO) ===" << endl;
			arbolTarjetasPorNumero->mostrar();
		}
	}

	// ========================================
	// HITO 2: METODOS DEL SEGUNDO ARBOL AVL (POR MONTO)
	// ========================================

	// Insertar tarjeta en el segundo árbol AVL (por saldo/monto)
	// Big O: O(log n) garantizado
	void insertarEnArbolPorMonto(double monto) {
		if (arbolTarjetasPorMonto != nullptr) {
			TarjetaPorMonto registro(monto, num_tarjeta);
			arbolTarjetasPorMonto->insertar(registro);
			cout << "Tarjeta " << num_tarjeta << " insertada en ARBOL 2 (por monto: $"
				<< monto << ")" << endl;
		}
	}

	// Buscar tarjeta por monto en el segundo árbol
	// Big O: O(log n)
	static bool buscarEnArbolPorMonto(double monto, string numTarjeta) {
		if (arbolTarjetasPorMonto != nullptr) {
			TarjetaPorMonto busqueda(monto, numTarjeta);
			return arbolTarjetasPorMonto->Buscar(busqueda);
		}
		return false;
	}

	// Mostrar todas las tarjetas ordenadas por monto (recorrido InOrden)
	// Big O: O(n)
	static void mostrarArbol2Ordenado() {
		if (arbolTarjetasPorMonto != nullptr) {
			cout << "\n=== ARBOL 2: TARJETAS ORDENADAS POR MONTO ===" << endl;
			cout << "Cantidad: " << arbolTarjetasPorMonto->cantidad()
				<< " | Altura: " << arbolTarjetasPorMonto->altura() << endl;
			arbolTarjetasPorMonto->enOrden();
			cout << endl;
		}
	}

	// Mostrar estructura del segundo árbol
	// Big O: O(n)
	static void mostrarEstructuraArbol2() {
		if (arbolTarjetasPorMonto != nullptr) {
			cout << "\n=== ESTRUCTURA DEL ARBOL 2 (POR MONTO) ===" << endl;
			arbolTarjetasPorMonto->mostrar();
		}
	}

	// Comparar búsqueda en ambos árboles
	// Big O: O(log n)
	static void compararBusquedaEnArboles(string numTarjeta, double monto) {
		cout << "\n=== COMPARACION DE BUSQUEDA EN 2 ARBOLES AVL ===" << endl;
		cout << "Buscando tarjeta: " << numTarjeta << " con monto: $" << monto << endl;

		// Búsqueda en árbol 1 (por número)
		bool encontrado1 = buscarEnArbolPorNumero(numTarjeta);
		cout << "Arbol 1 (por numero): " << (encontrado1 ? "ENCONTRADA" : "NO encontrada") << endl;

		// Búsqueda en árbol 2 (por monto)
		bool encontrado2 = buscarEnArbolPorMonto(monto, numTarjeta);
		cout << "Arbol 2 (por monto): " << (encontrado2 ? "ENCONTRADA" : "NO encontrada") << endl;
	}

	// ========================================
	// HITO 2: METODOS DEL GRAFO
	// ========================================

	// Registrar transferencia en el grafo
	// Big O: O(log n)
	void registrarTransferencia(string tarjetaDestino, double monto, string fecha) {
		if (grafoTransferencias != nullptr) {
			Transferencia trans;
			trans.origen = num_tarjeta;
			trans.destino = tarjetaDestino;
			trans.monto = monto;
			trans.fecha = fecha;

			(*grafoTransferencias)[num_tarjeta].push_back(trans);
			cout << "Transferencia registrada: " << num_tarjeta << " -> " << tarjetaDestino
				<< " ($" << monto << ")" << endl;
		}
	}

	// Mostrar transferencias de esta tarjeta
	// Big O: O(k) donde k = numero de transferencias
	void mostrarMisTransferencias() const {
		if (grafoTransferencias == nullptr) {
			cout << "No hay transferencias registradas" << endl;
			return;
		}

		auto it = grafoTransferencias->find(num_tarjeta);
		if (it != grafoTransferencias->end() && !it->second.empty()) {
			cout << "\n=== TRANSFERENCIAS DE " << num_tarjeta << " ===" << endl;
			for (const auto& trans : it->second) {
				cout << "  -> " << trans.destino << " ($" << trans.monto
					<< ") [" << trans.fecha << "]" << endl;
			}
		}
		else {
			cout << "Esta tarjeta no ha realizado transferencias" << endl;
		}
	}

	// Mostrar todo el grafo de transferencias
	// Big O: O(V + E)
	static void mostrarGrafoCompleto() {
		if (grafoTransferencias == nullptr || grafoTransferencias->empty()) {
			cout << "No hay transferencias registradas" << endl;
			return;
		}

		cout << "\n=== RED DE TRANSFERENCIAS COMPLETA ===" << endl;
		int totalTransferencias = 0;
		for (const auto& par : *grafoTransferencias) {
			if (!par.second.empty()) {
				cout << "\nTarjeta " << par.first << " realizo:" << endl;
				for (const auto& trans : par.second) {
					cout << "  -> " << trans.destino << " ($" << trans.monto
						<< ") [" << trans.fecha << "]" << endl;
					totalTransferencias++;
				}
			}
		}
		cout << "\nTotal de transferencias: " << totalTransferencias << endl;
	}

	// Recorrido BFS desde una tarjeta
	// Big O: O(V + E)
	static void recorridoBFS(string inicio) {
		if (grafoTransferencias == nullptr) {
			cout << "Grafo no inicializado" << endl;
			return;
		}

		set<string> visitados;
		queue<string> cola;

		cola.push(inicio);
		visitados.insert(inicio);

		cout << "\n=== RECORRIDO BFS desde " << inicio << " ===" << endl;
		cout << "Tarjetas alcanzables: ";

		while (!cola.empty()) {
			string actual = cola.front();
			cola.pop();
			cout << actual << " ";

			auto it = grafoTransferencias->find(actual);
			if (it != grafoTransferencias->end()) {
				for (const auto& trans : it->second) {
					if (visitados.find(trans.destino) == visitados.end()) {
						visitados.insert(trans.destino);
						cola.push(trans.destino);
					}
				}
			}
		}
		cout << endl;
	}

	// Recorrido DFS desde una tarjeta (RECURSIVO)
	// Big O: O(V + E)
	static void recorridoDFS(string inicio) {
		if (grafoTransferencias == nullptr) {
			cout << "Grafo no inicializado" << endl;
			return;
		}

		set<string> visitados;
		cout << "\n=== RECORRIDO DFS (RECURSIVO) desde " << inicio << " ===" << endl;
		cout << "Exploracion en profundidad: ";
		recorridoDFSRecursivo(inicio, visitados);
		cout << endl;
	}

	// Verificar si existe camino entre dos tarjetas
	// Big O: O(V + E)
	static bool existeCamino(string origen, string destino) {
		if (grafoTransferencias == nullptr) return false;

		set<string> visitados;
		queue<string> cola;

		cola.push(origen);
		visitados.insert(origen);

		while (!cola.empty()) {
			string actual = cola.front();
			cola.pop();

			if (actual == destino) return true;

			auto it = grafoTransferencias->find(actual);
			if (it != grafoTransferencias->end()) {
				for (const auto& trans : it->second) {
					if (visitados.find(trans.destino) == visitados.end()) {
						visitados.insert(trans.destino);
						cola.push(trans.destino);
					}
				}
			}
		}
		return false;
	}

	// Calcular total enviado por una tarjeta
	// Big O: O(k)
	double calcularTotalEnviado() const {
		double total = 0;
		if (grafoTransferencias != nullptr) {
			auto it = grafoTransferencias->find(num_tarjeta);
			if (it != grafoTransferencias->end()) {
				for (const auto& trans : it->second) {
					total += trans.monto;
				}
			}
		}
		return total;
	}
};

// Inicialización de atributos estáticos - ARBOL 1
template <typename T>
ArbolAVL<string>* Tarjetas<T>::arbolTarjetasPorNumero = nullptr;

template <typename T>
bool Tarjetas<T>::arbol1Inicializado = false;

// Inicialización de atributos estáticos - ARBOL 2
template <typename T>
ArbolAVL<typename Tarjetas<T>::TarjetaPorMonto>* Tarjetas<T>::arbolTarjetasPorMonto = nullptr;

template <typename T>
bool Tarjetas<T>::arbol2Inicializado = false;

// Inicialización de atributos estáticos - GRAFO
template <typename T>
map<string, vector<typename Tarjetas<T>::Transferencia>>* Tarjetas<T>::grafoTransferencias = nullptr;

template <typename T>
bool Tarjetas<T>::grafoInicializado = false;
