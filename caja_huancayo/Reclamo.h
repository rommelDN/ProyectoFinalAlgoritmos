#pragma once
#include <ctime>
#include <sstream>
#include<string>
#include <iostream>
#include <vector>

using namespace std;

template <typename T1, typename T2>
class Reclamo {
private:
	T1 id_reclamo;       //String
	T1 id_seguro;        // CLAVE FORÁNEA - referencia al seguro
	T1 id_cliente;
	T1 descripcion;     //String
	T1 fecha;           //String
	T1 estado;          //String: "ABIERTO", "EN PROCESO", "CERRADO"
	T2 montoReclamado;
	T2 montoAprobado;

	string generarID() {
		static int contador = 1;
		return "RCL-" + to_string(contador++);
	}
public:
	Reclamo(T1 id_seg, T1 id_cli, T1 desc, T1 f, T2 monto_rec) 
		: id_seguro(id_seg), id_cliente(id_cli), descripcion(desc), fecha(f), montoReclamado(monto_rec) {
		id_reclamo = generarID();
		estado = "ABIERTO";
		montoAprobado = 0;
	}
	//getters
	T1 getIdReclamo() { return id_reclamo; }
	T1 getIdSeguro() { return id_seguro; }
	T1 getIdCliente() { return id_cliente; }
	T1 getDescripcion() { return descripcion; }
	T1 getFecha() { return fecha; }
	T1 getEstado() { return estado; }
	T2 getMontoReclamado() { return montoReclamado; }
	T2 getMontoAprobado() { return montoAprobado; }
	//setters
	void setEstado(T1 est) { estado = est; }
	void setMontoAprobado(T2 monto) { montoAprobado = monto; }
	void setDescripcion(T1 desc) { descripcion = desc; }
	// Métodos de transición de estado
	void abrir() { 
		estado = "ABIERTO"; 
	}
	void ponerEnProceso() { 
		estado = "PENDIENTE"; 
	}
	void aprobar(T2 montoAprobado = 0) {
		estado = "APROBADO";
		if (montoAprobado > 0) this->montoAprobado = montoAprobado;
	}
	void rechazar() { 
		estado = "RECHAZADO"; 
	}
	void cerrar() { 
		estado = "CERRADO"; 
	}
	//Estados
	bool estaAbierto() const {
		return estado == "ABIERTO";
	}
	bool estaEnProceso() const {
		return estado == "EN PROCESO";
	}
	bool estaCerrado() const {
		return estado == "CERRADO";
	}
	bool estaAprobado() const {
		return estado == "APROBADO";
	}
	bool estaRechazado() const { 
		return estado == "RECHAZADO"; 
	}

	void mostrarInfo() const {
		cout << "ID Reclamo: " << id_reclamo << endl;
		cout << "ID Seguro: " << id_seguro << endl;
		cout << "ID Cliente: " << id_cliente << endl;
		cout << "Descripcion: " << descripcion << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Estado: " << estado << endl;
		cout << "Monto Reclamado: " << montoReclamado << endl;
		cout << "Monto Aprobado: " << montoAprobado << endl;
	}
};