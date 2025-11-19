#pragma once
#include"servicios.h"
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


	// Composición con reclamos
	ListaEnlazada<Beneficiario<string, double>>* beneficiarios;

	Pila<Reclamo<string, double>>* HistorialReclamos;  // Para ver los más recientes
	Cola<Reclamo<string, double>>* reclamosPendientes; // Para procesar en orden

	string generarID() {
		static int contador = 1;
		return "SG-" + to_string(contador++);
	}

	//LISTA ESTÁTICA COMPARTIDA para todos los objetos Cuenta
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

	string calcularFechaVencimiento(T1 fecha_inicio, T2 meses_cov) {
		tm tm = {};
		istringstream ss(fecha_inicio);
		ss >> get_time(&tm, "%d/%m/%Y");  // Cambiado al formato correcto
		if (ss.fail()) {
			throw runtime_error("Error al parsear la fecha de inicio.");
		}
		tm.tm_mon += static_cast<int>(meses_cov);
		mktime(&tm);
		ostringstream os;
		os << put_time(&tm, "%Y-%m-%d");  // Puedes cambiar esto también si quieres
		return os.str();
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
			Transaccion<string, double> pago("PAGO_SEGURO", reclamo.getMontoAprobado(), "Sistema");
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
			cout << "------------------------" << endl;});
		
	}

	// Sobrecarga del operador << para poder imprimir
	friend ostream& operator<<(ostream& os, const Seguros& e) {
		os <<"( " << e.getIdSeguro() << " | "
			<< e.getTipoSeguro() << " | "
			<< e.getMesesCobertura() << " | "
			<< e.getPrimaMensual() << " | "
			<< e.getFechaVencimiento() << " | "
			<< e.getEstadoPoliza() << " | "
			<< e.getMontoCobertura()<<" )";
		return os;
	}


};

