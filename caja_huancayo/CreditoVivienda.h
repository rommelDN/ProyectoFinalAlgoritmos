#pragma once
#include<iostream>
#include "Credito.h"
using namespace std;
template <typename T1, typename T2>
class CreditoVivienda : public Credito<string, double> {
private:
	T1 id_credito_vivienda; //string
	T1 direccion_propiedad;	//string
	T2 valor_propiedad;		//double
	string generarID() {
		static int contador = 1;
		return "CRV-" + to_string(contador++);
	};
public:
	CreditoVivienda(T1 n_cuenta, T1 t, T1 f_a, double monto_prestamo, int plazo_meses, double tasa_interes,
		T1 direccion_propiedad, double valor_propiedad)
		: Credito<string, double>(n_cuenta, t, f_a, monto_prestamo, plazo_meses, tasa_interes),
		direccion_propiedad(direccion_propiedad), valor_propiedad(valor_propiedad) {
		id_credito_vivienda = generarID();
	}
	//getters
	T1 getIdCreditoVivienda() { return id_credito_vivienda; }
	T1 getDireccionPropiedad() { return direccion_propiedad; }
	T2 getValorPropiedad() { return valor_propiedad; }
	//setters
	void setDireccionPropiedad(T1 direccion_propiedad) { this->direccion_propiedad = direccion_propiedad; }
	void setValorPropiedad(T2 valor_propiedad) { this->valor_propiedad = valor_propiedad; }

	void registrarHipoteca() {
		cout << "Registrando hipoteca para el inmueble en: " << this->getDireccionPropiedad() << endl;
		cout << "Valor del inmueble: $" << this->getValorPropiedad() << endl;
		cout << "Monto del crédito: $" << this->getMontoPrestamo() << endl;
	}

	void mostrarInfo() const {
		Credito<string, double>::mostrarInfo();
		cout << "ID Credito Vivienda: " << id_credito_vivienda
			<< " | Direccion Propiedad: " << direccion_propiedad
			<< " | Valor Propiedad: $" << valor_propiedad << endl;
	}
	void desembolsar() {
		cout << "Desembolsando CREDITO VIVIENDA" << endl;
		cout << "Direccion de la propiedad: " << direccion_propiedad << endl;
		Credito<string, double>::desembolsar();
	}
};