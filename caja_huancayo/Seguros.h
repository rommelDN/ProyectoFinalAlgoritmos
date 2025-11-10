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
	ListaEnlazada<Reclamo<string, double>>* reclamos;
	Pila<Reclamo<string, double>>* reclamosRecientes;  // Para ver los más recientes
	Cola<Reclamo<string, double>>* reclamosPendientes; // Para procesar en orden

	string generarID() {
		static int contador = 1;
		return "SG-" + to_string(contador++);
	}

	//LISTA ESTÁTICA COMPARTIDA para todos los objetos Cuenta
	static ListaEnlazada<Servicios<string, double>>* listaServiciosGlobal;

public:
	Seguros(T1 n_cuenta, T1 t, T1 f_a, T1 t_seguro, T2 meses_cov, T2 prima_mensual, T2 monto_cov)
		: Servicios<string, double>(n_cuenta, t, f_a), tipo_seguro(t_seguro), meses_cobertura(meses_cov),
		prima_mensual(prima_mensual), monto_cobertura(monto_cov) {
		id_seguro = generarID();
		estado_poliza = "ACTIVA";
		fecha_vencimiento = calcularFechaVencimiento(f_a, meses_cov);
		beneficiarios = new ListaEnlazada<Beneficiario<string, double>>();
		reclamos = new ListaEnlazada<Reclamo<string, double>>();
		reclamosRecientes = new Pila<Reclamo<string, double>>();
		reclamosPendientes = new Cola<Reclamo<string, double>>();
		if (listaServiciosGlobal != nullptr) {
			listaServiciosGlobal->agregarFinal(*this);
		}
	}
	static void setListaServiciosGlobal(ListaEnlazada<Servicios<string, double>>& lista) {
		listaServiciosGlobal = &lista;
	}
	//getters
	T1 getIdSeguro() { return id_seguro; }
	T1 getTipoSeguro() { return tipo_seguro; }
	T2 getMesesCobertura() { return meses_cobertura; }
	T2 getPrimaMensual() { return prima_mensual; }
	T1 getFechaVencimiento() { return fecha_vencimiento; }
	T1 getEstadoPoliza() { return estado_poliza; }
	T2 getMontoCobertura() { return monto_cobertura; }
	//setters
	void setTipoSeguro(T1 t_seguro) { tipo_seguro = t_seguro; }
	void setMesesCobertura(T2 meses_cov) { meses_cobertura = meses_cov; }
	void setPrimaMensual(T2 prima_mensual) { this->prima_mensual = prima_mensual; }
	void setMontoCobertura(T2 monto_cov) { monto_cobertura = monto_cov; }
	
	void crearBeneficiario(string id_seguro, string dni, string n, string r, double p, ListaEnlazada<Cliente<string>>& listaClientes) {
		Cliente<string> cliente;
		try {
			cliente = Cliente<string>::obtenerXdni(listaClientes, dni);
			Beneficiario<string, double> nuevoBeneficiario(id_seguro, cliente.getID(), n, r, p);
			beneficiarios->agregarFinal(nuevoBeneficiario);
			cout << "Beneficiario creado con exito." << endl;

		}
		catch (const exception& e) {
			cout << "Error al buscar cliente: " << e.what() << endl;

		}
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
		reclamos->agregarFinal(nuevoReclamo);
		reclamosRecientes->apilar(nuevoReclamo);
		reclamosPendientes->encolar(nuevoReclamo);
		cout << "Reclamo creado con ID: " << nuevoReclamo.getIdReclamo() << endl;
	}

	// Procesar siguiente reclamo pendiente
	void procesarSiguienteReclamo() {
		if (reclamosPendientes->estaVacia()) {
			cout << "No hay reclamos pendientes por procesar." << endl;
			return;
		}

		Reclamo<string, double> reclamo = reclamosPendientes->getFrente();
		reclamosPendientes->desencolar();

		cout << "Procesando reclamo: " << reclamo.getIdReclamo() << endl;
		reclamo.mostrarInfo();

		// Aquí iría la lógica de evaluación del reclamo
		evaluarReclamo(reclamo);
	}

	// Evaluar y decidir sobre el reclamo
	void evaluarReclamo(Reclamo<string, double>& reclamo) {
		reclamo.ponerEnProceso();

		// Simulación de evaluación
		if (reclamo.getMontoReclamado() <= this->getMontoCobertura() * 0.8) {
			// Aprobar reclamo
			reclamo.aprobar(reclamo.getMontoReclamado());
			cout << "Reclamo APROBADO. Monto a pagar: $" << reclamo.getMontoAprobado() << endl;

			// Crear transacción de pago
			Transaccion<string, double>pago("PAGO_SEGURO", reclamo.getMontoAprobado(), "Sistema");
			pago.completar();
			this->agrearTransaccion(pago);

		}
		else {
			// Rechazar reclamo
			reclamo.rechazar();
			cout << "Reclamo RECHAZADO. Monto excede cobertura." << endl;
		}

		// Actualizar en la lista principal
		actualizarReclamoEnLista(reclamo);
	}
	// Actualizar reclamo en la lista principal
	void actualizarReclamoEnLista(const Reclamo<string, double>& reclamoActualizado) {
		// Buscar y actualizar el reclamo en la lista principal
		auto nodoActual = reclamos->getCabeza();
		while (nodoActual != nullptr) {
			if (nodoActual->getDato().getIdReclamo() == reclamoActualizado.getIdReclamo()) {
				nodoActual->getDato() = reclamoActualizado;
				break;
			}
			nodoActual = nodoActual->getSiguiente();
		}
	}

};

template<typename T1, typename T2>
ListaEnlazada<Servicios<string, double>>* Seguros<T1, T2>::listaServiciosGlobal = nullptr;