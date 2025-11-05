#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2>
class Beneficiario {
private:
	T1 id_beneficiario; // String
	T1 id_seguro;        // CLAVE FORÁNEA - referencia al seguro
	T1 id_cliente;
	T1 nombre;        // String
	T1 relacion;      // String
	T2 porcentaje;    // Double

	string generarID() {
		static int contador = 1;
		return "BEN-" + to_string(contador++);
	}
public:
	Beneficiario(T1 id_seg, T1 id_cli,T1 n, T1 r, T2 p) : id_seguro(id_seg), id_cliente(id_cli), nombre(n), relacion(r), porcentaje(p) {
		id_beneficiario = generarID();
	}
	// Getters
	T1 getIdSeguro() { return id_seguro; }
	T1 getIdCliente() { return id_cliente; }
	T1 getNombre() const { return nombre; }
	T1 getRelacion() const { return relacion; }
	T2 getPorcentaje() const { return porcentaje; }
	// Setters
	void setNombre(T1 n) { nombre = n; }
	void setRelacion(T1 r) { relacion = r; }
	void setPorcentaje(T2 p) { porcentaje = p; }

	void mostrarInfo() const {
		cout << "Beneficiario ID: " << id_beneficiario << endl;
		cout << "ID Seguro: " << id_seguro << endl;
		cout << "ID Cliente: " << id_cliente << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Relacion: " << relacion << endl;
		cout << "Porcentaje: " << porcentaje << "%" << endl;

	}
};