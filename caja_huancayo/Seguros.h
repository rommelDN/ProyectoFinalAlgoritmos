#pragma once
#include"servicios.h"
#include"Reclamo.h"
#include"Beneficiario.h"
#include"GrafoBeneficiaro.h" // ¡NUEVA INCLUSIÓN!
#include <ctime>
#include <iomanip>
#include <sstream>
#include"ListaEnlazada.h"
#include "Pila.h"
#include "Cola.h"
#include "Cliente.h"
#include"HashTable.h"

template <typename T1, typename T2>
class Seguros : public Servicios<string, double> {
private:
	T1 id_seguro;
	T1 tipo_seguro;
	T2 meses_cobertura;
	T2 prima_mensual;
	T1 fecha_vencimiento;
	T1 estado_poliza;
	T2 monto_cobertura;

	// Estructuras existentes
	ListaEnlazada<Beneficiario<string, double>>* beneficiarios;
	Pila<Reclamo<string, double>>* HistorialReclamos;
	Cola<Reclamo<string, double>>* reclamosPendientes;

	// ¡NUEVA ESTRUCTURA DE GRAFO!
	GrafoBeneficiarios<string, double>* redBeneficiarios;

	string generarID() {
		static int contador = 1;
		return "SG-" + to_string(contador++);
	}

	static HashTable<Servicios<string, double>>* tablaServiciosGlobal;

public:
	Seguros(T1 n_cuenta, T1 t, T1 f_a, T1 t_seguro, T2 meses_cov, T2 prima_mensual, T2 monto_cov)
		: Servicios<string, double>(n_cuenta, t, f_a), tipo_seguro(t_seguro), meses_cobertura(meses_cov),
		prima_mensual(prima_mensual), monto_cobertura(monto_cov) {
		id_seguro = generarID();
		estado_poliza = "ACTIVA";
		fecha_vencimiento = calcularFechaVencimiento(f_a, meses_cov);
		beneficiarios = new ListaEnlazada<Beneficiario<string, double>>();
		HistorialReclamos = new Pila<Reclamo<string, double>>();
		reclamosPendientes = new Cola<Reclamo<string, double>>();
		redBeneficiarios = new GrafoBeneficiarios<string, double>();

		if (tablaServiciosGlobal != nullptr) {
			tablaServiciosGlobal->insertar(n_cuenta, *this);
		}
	}

	/*~Seguros() {
		delete beneficiarios;
		delete HistorialReclamos;
		delete reclamosPendientes;
		delete redBeneficiarios;
	}*/

	static void setTablaServiciosGlobal(HashTable<Servicios<string, double>>& tabla) {
		tablaServiciosGlobal = &tabla;
	}

	// Getters existentes
	T1 getIdSeguro()const { return id_seguro; }
	T1 getTipoSeguro()const { return tipo_seguro; }
	T2 getMesesCobertura()const { return meses_cobertura; }
	T2 getPrimaMensual()const { return prima_mensual; }
	T1 getFechaVencimiento()const { return fecha_vencimiento; }
	T1 getEstadoPoliza()const { return estado_poliza; }
	T2 getMontoCobertura()const { return monto_cobertura; }

	// Setters existentes
	void setTipoSeguro(T1 t_seguro) { tipo_seguro = t_seguro; }
	void setMesesCobertura(T2 meses_cov) { meses_cobertura = meses_cov; }
	void setPrimaMensual(T2 prima_mensual) { this->prima_mensual = prima_mensual; }
	void setMontoCobertura(T2 monto_cov) { monto_cobertura = monto_cov; }

	// ========== NUEVOS MÉTODOS PARA EL GRAFO ==========

	// Agregar beneficiario con integración al grafo
	void crearBeneficiarioConGrafo(Seguros<string, double>* seguro, Cliente<string>* cliente,
		const string& nombre, const string& relacion, double porcentaje) {
		// Crear beneficiario en la lista enlazada (método existente)
		Beneficiario<string, double> nuevo(seguro->getIdSeguro(), cliente->getID(), nombre, relacion, porcentaje);
		seguro->beneficiarios->agregarFinal(nuevo);

		// Agregar al grafo usando el nombre como ID único
		string id_beneficiario = nombre + "_" + cliente->getID();
		seguro->redBeneficiarios->agregarBeneficiario(id_beneficiario, nombre, porcentaje);

		cout << "Beneficiario '" << nombre << "' agregado con éxito a la lista y al grafo.\n";
	}

	// Crear relación de dependencia entre beneficiarios
	void crearRelacionBeneficiarios(const string& nombre_origen, const string& id_cliente_origen,
		const string& nombre_destino, const string& id_cliente_destino,
		double peso, const string& tipo_relacion) {
		string id_origen = nombre_origen + "_" + id_cliente_origen;
		string id_destino = nombre_destino + "_" + id_cliente_destino;

		redBeneficiarios->crearRelacion(id_origen, id_destino, peso, tipo_relacion);
	}

	// Mostrar la red completa de beneficiarios
	void mostrarRedBeneficiarios() {
		cout << "\n========================================\n";
		cout << "  RED DE BENEFICIARIOS - SEGURO " << id_seguro << "\n";
		cout << "========================================\n";
		redBeneficiarios->mostrarGrafo();
	}

	// Análisis de beneficiarios conectados
	void analizarBeneficiariosConectados(const string& nombre, const string& id_cliente) {
		string id_beneficiario = nombre + "_" + id_cliente;
		redBeneficiarios->beneficiariosConectados(id_beneficiario);
	}

	// Detectar conflictos de interés
	void detectarConflictosInteres() {
		cout << "\n----- Analisis de Conflictos -----\n";
		bool hay_ciclos = redBeneficiarios->detectarCiclos();
		if (!hay_ciclos) {
			cout << "No se detectaron conflictos de interés en la red.\n";
		}
	}

	// Validar distribución de porcentajes
	void validarDistribucionBeneficiarios() {
		cout << "\n----- Validacion de Distribucion -----\n";
		redBeneficiarios->validarDistribucion();
	}

	// Mostrar beneficiarios más influyentes
	void mostrarBeneficiariosInfluyentes(int top = 3) {
		if (redBeneficiarios->estaVacio()) {
			cout << "No hay beneficiarios en el grafo.\n";
			return;
		}
		redBeneficiarios->beneficiariosMasInfluyentes(top);
	}

	// Encontrar beneficiarios principales
	void mostrarBeneficiariosPrincipales() {
		if (redBeneficiarios->estaVacio()) {
			cout << "No hay beneficiarios en el grafo.\n";
			return;
		}
		redBeneficiarios->encontrarBeneficiariosPrincipales();
	}

	// Calcular distribución acumulada para un beneficiario y su red
	void calcularDistribucionAcumulada(const string& nombre, const string& id_cliente) {
		string id_beneficiario = nombre + "_" + id_cliente;
		double distribucion = redBeneficiarios->calcularDistribucionAcumulada(id_beneficiario);
		cout << "\nDistribución acumulada para " << nombre << " y su red: "
			<< distribucion << "%\n";
	}

	// ========== MÉTODOS EXISTENTES (sin cambios) ==========

	void mostrarBeneficiarios() {
		if (beneficiarios->estaVacia()) {
			cout << "No hay beneficiarios registrados para este seguro." << endl;
			return;
		}
		cout << "Beneficiarios del Seguro " << id_seguro << ":" << endl;
		beneficiarios->mostrarTodo();
	}

	string sumarMesesRecursivo(tm fecha, int meses_restantes) {
		if (meses_restantes == 0) {
			mktime(&fecha);
			ostringstream os;
			os << put_time(&fecha, "%Y-%m-%d");
			return os.str();
		}
		fecha.tm_mon += 1;
		mktime(&fecha);
		return sumarMesesRecursivo(fecha, meses_restantes - 1);
	}

	string calcularFechaVencimiento(T1 fecha_inicio, T2 meses_cov) {
		tm fecha = {};
		istringstream ss(fecha_inicio);
		ss >> get_time(&fecha, "%d/%m/%Y");
		if (ss.fail()) {
			throw runtime_error("Error al parsear la fecha de inicio.");
		}
		return sumarMesesRecursivo(fecha, static_cast<int>(meses_cov));
	}

	void crearReclamo(T1 id_seguro, T1 id_cliente, T1 descripcion, T1 fecha, T2 monto_reclamado) {
		Reclamo<string, double> nuevoReclamo(id_seguro, id_cliente, descripcion, fecha, monto_reclamado);
		reclamosPendientes->encolar(nuevoReclamo);
		cout << "Reclamo Enviado con ID: " << nuevoReclamo.getIdReclamo() << endl;
	}

	bool procesarReclamosEncolados() {
		if (reclamosPendientes->estaVacia()) {
			cout << "No hay reclamos pendientes.\n";
			return false;
		}
		char opcion;
		while (!reclamosPendientes->estaVacia()) {
			Reclamo<string, double>& reclamo = reclamosPendientes->getFrenteRef();
			bool aprobado = evaluarReclamo(reclamo);
			HistorialReclamos->apilar(reclamo);
			reclamosPendientes->desencolar();

			if (!reclamosPendientes->estaVacia()) {
				cout << "\n¿Desea procesar el siguiente reclamo? (s/n): ";
				cin >> opcion;
				if (opcion == 'n' || opcion == 'N') {
					cout << "Procesamiento detenido por el usuario.\n";
					return true;
				}
			}
		}
		cout << "Todos los reclamos pendientes fueron procesados.\n";
		return true;
	}

	bool evaluarReclamo(Reclamo<string, double>& reclamo) {
		reclamo.ponerEnProceso();
		cout << "Evaluando reclamo (EN PROCESO) ID: "
			<< reclamo.getIdReclamo()
			<< " | Monto Reclamado: $"
			<< reclamo.getMontoReclamado() << endl;

		if (reclamo.getMontoReclamado() <= this->getMontoCobertura() * 0.8) {
			reclamo.aprobar(reclamo.getMontoReclamado());
			cout << "Reclamo APROBADO. Monto a pagar: $"
				<< reclamo.getMontoAprobado() << endl;
			Transaccion<string, double> pago("RETIRO", reclamo.getMontoAprobado(), "Sistema");
			pago.completar();
			this->agrearTransaccion(pago);
			return true;
		}

		reclamo.rechazar();
		cout << "Reclamo RECHAZADO. Monto excede cobertura." << endl;
		return false;
	}

	void mostrar() const {
		cout << "ID Seguro: " << id_seguro
			<< " | Tipo Seguro: " << tipo_seguro
			<< " | Meses Cobertura: " << meses_cobertura
			<< " | Prima Mensual: $" << prima_mensual
			<< " | Fecha Vencimiento: " << fecha_vencimiento
			<< " | Estado Poliza: " << estado_poliza
			<< " | Monto Cobertura: $" << monto_cobertura << endl;
	}

	void mostrarColaReclamos() {
		if (reclamosPendientes->estaVacia()) {
			cout << "No hay reclamos pendientes." << endl;
			return;
		}
		cout << "Reclamos Pendientes:" << endl;
		reclamosPendientes->mostrar([](const Reclamo<string, double>& r) {
			r.mostrarInfo();
			cout << "------------------------" << endl;
			});
	}

	void mostrarHistorialReclamos() {
		if (HistorialReclamos->estaVacia()) {
			cout << "No hay reclamos en el historial." << endl;
			return;
		}
		cout << "\n===== HISTORIAL DE RECLAMOS =====\n";
		HistorialReclamos->mostrar([](const Reclamo<string, double>& r) {
			r.mostrarInfo();
			cout << "------------------------" << endl;
			});
	}

	friend ostream& operator<<(ostream& os, const Seguros& e) {
		os << "( " << "ID:" << e.getIdSeguro() << " | "
			<< "Tipo Seguro :" << e.getTipoSeguro() << " | "
			<< "Meses Covertura : " << e.getMesesCobertura() << " | "
			<< "Prima Mensual : " << e.getPrimaMensual() << " | "
			<< "Fecha Vencimiento : " << e.getFechaVencimiento() << " | "
			<< "Estado Poliza: " << e.getEstadoPoliza() << " | "
			<< "Monto Covertura: " << e.getMontoCobertura() << " )";
		return os;
	}
};


/*#include"servicios.h"
#include"Reclamo.h"
#include"Beneficiario.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include"ListaEnlazada.h"
#include "Pila.h"
#include "Cola.h"
#include "Cliente.h"
#include"HashTable.h"
////////////////////////////
//USO DE TEMPLATES
////////////////////////////
template <typename T1, typename T2>
class Seguros : public Servicios<string, double> {
private:
	T1 id_seguro;			//String	
	T1 tipo_seguro;			//String: "VIDA", "HOGAR", "AUTO"
	T2 meses_cobertura;		//Double
	T2 prima_mensual;		//Double
	T1 fecha_vencimiento;	//String
	T1 estado_poliza;		//String: "ACTIVA", "VENCIDA", "CANCELADA"
	T2 monto_cobertura;		//Double


	
	/////////////////////////////
	//Estructuras para Beneficiarios y Reclamos
	/////////////////////////////
	ListaEnlazada<Beneficiario<string, double>>* beneficiarios;
	Pila<Reclamo<string, double>>* HistorialReclamos;  // Para ver los más recientes
	Cola<Reclamo<string, double>>* reclamosPendientes; // Para procesar en orden

	string generarID() {
		static int contador = 1;
		return "SG-" + to_string(contador++);
	}
	////////////////////////////////
	//HASH TABLA COMPARTIDA para todos los objetos Cuenta
	////////////////////////////////
	static HashTable<Servicios<string, double>>* tablaServiciosGlobal;

public:
	Seguros(T1 n_cuenta, T1 t, T1 f_a, T1 t_seguro, T2 meses_cov, T2 prima_mensual, T2 monto_cov)
		: Servicios<string, double>(n_cuenta, t, f_a), tipo_seguro(t_seguro), meses_cobertura(meses_cov),
		prima_mensual(prima_mensual), monto_cobertura(monto_cov) {
		id_seguro = generarID();
		estado_poliza = "ACTIVA";
		fecha_vencimiento = calcularFechaVencimiento(f_a, meses_cov);
		beneficiarios = new ListaEnlazada<Beneficiario<string, double>>();
		HistorialReclamos = new Pila<Reclamo<string, double>>();
		reclamosPendientes = new Cola<Reclamo<string, double>>();
		
		if (tablaServiciosGlobal != nullptr) {
			tablaServiciosGlobal->insertar(n_cuenta, *this);
		}
	}

	static void setTablaServiciosGlobal(HashTable<Servicios<string, double>>& tabla) {
		tablaServiciosGlobal = &tabla;
	}

	//getters
	T1 getIdSeguro()const { return id_seguro; }
	T1 getTipoSeguro()const { return tipo_seguro; }
	T2 getMesesCobertura()const { return meses_cobertura; }
	T2 getPrimaMensual()const { return prima_mensual; }
	T1 getFechaVencimiento()const { return fecha_vencimiento; }
	T1 getEstadoPoliza()const { return estado_poliza; }
	T2 getMontoCobertura()const { return monto_cobertura; }
	//setters
	void setTipoSeguro(T1 t_seguro) { tipo_seguro = t_seguro; }
	void setMesesCobertura(T2 meses_cov) { meses_cobertura = meses_cov; }
	void setPrimaMensual(T2 prima_mensual) { this->prima_mensual = prima_mensual; }
	void setMontoCobertura(T2 monto_cov) { monto_cobertura = monto_cov; }

	void crearBeneficiarioHash(Seguros<string, double>* seguro,Cliente<string>* cliente,const string& nombre,const string& relacion,double porcentaje) {
		Beneficiario<string, double> nuevo(seguro->getIdSeguro(),cliente->getID(),nombre,relacion,porcentaje);
		seguro->beneficiarios->agregarFinal(nuevo);
		cout << "Beneficiario agregado con éxito.\n";
	}

	void mostrarBeneficiarios() {
		if (beneficiarios->estaVacia()) {
			cout << "No hay beneficiarios registrados para este seguro." << endl;
			return;
		}
		cout << "Beneficiarios del Seguro " << id_seguro << ":" << endl;
		beneficiarios->mostrarTodo();
	}
	/////////////////////////////////
	//Funcion Recursiva
	/////////////////////////////////
	string sumarMesesRecursivo(tm fecha, int meses_restantes) {
		// Caso base: ya no hay meses por sumar
		if (meses_restantes == 0) {
			// Normalizar fecha
			mktime(&fecha);
			ostringstream os;
			os << put_time(&fecha, "%Y-%m-%d");
			return os.str();
		}
		fecha.tm_mon += 1;
		mktime(&fecha); // Normaliza por si pasa de diciembre

		return sumarMesesRecursivo(fecha, meses_restantes - 1);
	}
	string calcularFechaVencimiento(T1 fecha_inicio, T2 meses_cov) {
		tm fecha = {};
		istringstream ss(fecha_inicio);
		ss >> get_time(&fecha, "%d/%m/%Y");
		if (ss.fail()) {
			throw runtime_error("Error al parsear la fecha de inicio.");
		}

		return sumarMesesRecursivo(fecha, static_cast<int>(meses_cov));
	}


	void crearReclamo(T1 id_seguro,T1 id_cliente, T1 descripcion, T1 fecha, T2 monto_reclamado) {
		Reclamo<string, double> nuevoReclamo(id_seguro, id_cliente, descripcion, fecha, monto_reclamado);
		reclamosPendientes->encolar(nuevoReclamo); //Para el procesamiento en Cola de todas las solicitudes de reclamos
		cout << "Reclamo Enviado con ID: " << nuevoReclamo.getIdReclamo() << endl;
	}

	bool procesarReclamosEncolados() {
		if (reclamosPendientes->estaVacia()) {
			cout << "No hay reclamos pendientes.\n";
			return false;
		}
		char opcion;
		// Procesar mientras existan reclamos
		while (!reclamosPendientes->estaVacia()) {
			// Obtener referencia al reclamo actual (el primero de la cola)
			Reclamo<string, double>& reclamo = reclamosPendientes->getFrenteRef();
			bool aprobado = evaluarReclamo(reclamo);
			// Mover reclamo al historial siempre
			HistorialReclamos->apilar(reclamo);
			// Quitar de la cola
			reclamosPendientes->desencolar();
			// Si aún quedan reclamos, preguntar si desea continuar
			if (!reclamosPendientes->estaVacia()) {
				cout << "\n¿Desea procesar el siguiente reclamo? (s/n): ";
				cin >> opcion;

				if (opcion == 'n' || opcion == 'N') {
					cout << "Procesamiento detenido por el usuario.\n";
					return true;
				}
			}
		}
		cout << "Todos los reclamos pendientes fueron procesados.\n";
		return true;
	}

	bool evaluarReclamo(Reclamo<string, double>& reclamo) {
		reclamo.ponerEnProceso();
		cout << "Evaluando reclamo (EN PROCESO) ID: "
			<< reclamo.getIdReclamo()
			<< " | Monto Reclamado: $"
			<< reclamo.getMontoReclamado() << endl;
		// Si el monto es aceptable
		if (reclamo.getMontoReclamado() <= this->getMontoCobertura() * 0.8) {
			reclamo.aprobar(reclamo.getMontoReclamado());
			cout << "Reclamo APROBADO. Monto a pagar: $"
				<< reclamo.getMontoAprobado() << endl;
			Transaccion<string, double> pago("RETIRO", reclamo.getMontoAprobado(), "Sistema");
			pago.completar();
			this->agrearTransaccion(pago);

			return true;
		}

		// Reclamo rechazado
		reclamo.rechazar();
		cout << "Reclamo RECHAZADO. Monto excede cobertura." << endl;
		return false;
	}


	void mostrar() const  {
		cout << "ID Seguro: " << id_seguro
			<< " | Tipo Seguro: " << tipo_seguro
			<< " | Meses Cobertura: " << meses_cobertura
			<< " | Prima Mensual: $" << prima_mensual
			<< " | Fecha Vencimiento: " << fecha_vencimiento
			<< " | Estado Poliza: " << estado_poliza
			<< " | Monto Cobertura: $" << monto_cobertura << endl;

	}
	void mostrarColaReclamos() {
		if (reclamosPendientes->estaVacia()) {
			cout << "No hay reclamos pendientes." << endl;
			return;
		}
		cout << "Reclamos Pendientes:" << endl;
		/////////////////////////////
		// Uso de función lambda
		/////////////////////////////
		reclamosPendientes->mostrar([](const Reclamo<string, double>& r) {
			r.mostrarInfo();
			cout << "------------------------" << endl;
			});
	}
	void mostrarHistorialReclamos() {
		if (HistorialReclamos->estaVacia()) {
			cout << "No hay reclamos en el historial." << endl;
			return;
		}
		cout << "\n===== HISTORIAL DE RECLAMOS =====\n";
		/////////////////////////////
		// Uso de función lambda
		/////////////////////////////
		HistorialReclamos->mostrar([](const Reclamo<string, double>& r) {
			r.mostrarInfo();
			cout << "------------------------" << endl;});
		
	}

	// Sobrecarga del operador << para poder imprimir
	friend ostream& operator<<(ostream& os, const Seguros& e) {
		os <<"( " <<"ID:"<< e.getIdSeguro() << " | "
			<<"Tipo Seguro :"<< e.getTipoSeguro() << " | "
			<<"Meses Covertura : "<< e.getMesesCobertura() << " | "
			<<"Prima Mensual : " << e.getPrimaMensual() << " | "
			<<"Fecha Vencimiento : " << e.getFechaVencimiento() << " | "
			<<"Estado Poliza: " << e.getEstadoPoliza() << " | "
			<<"Monto Covertura: " << e.getMontoCobertura()<<" )";
		return os;
	}


};

*/