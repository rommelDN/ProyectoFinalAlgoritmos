#pragma once
#include<iostream>
#include "Credito.h"
using namespace std;

template <typename T1, typename T2>
class CreditoPersonal : public Credito<string, double> {
private:
	T1 id_credito_personal; //string
	T1 destino_credito;		//string
	T2 seguro_desgravamen;	//boolean
	string generarID() {
		static int contador = 1;
		return "CRP-" + to_string(contador++);
	};
public:
	CreditoPersonal(T1 n_cuenta, T1 t, T1 f_a, double monto_prestamo, int plazo_meses, double tasa_interes,
		T1 destino_credito, T2 seguro_desgravamen)
		: Credito<string, double>(n_cuenta, t, f_a, monto_prestamo, plazo_meses, tasa_interes),
		destino_credito(destino_credito), seguro_desgravamen(seguro_desgravamen) {
		id_credito_personal = generarID();
	}
	//getters
	T1 getIdCreditoPersonal() { return id_credito_personal; }
	T1 getDestinoCredito() { return destino_credito; }
	T2 getSeguroDesgravamen() { return seguro_desgravamen; }
	//setters
	void setDestinoCredito(T1 destino_credito) { this->destino_credito = destino_credito; }
	void setSeguroDesgravamen(T2 seguro_desgravamen) { this->seguro_desgravamen = seguro_desgravamen; }
	
	void mostrarInfo() const {
		Credito<string, double>::mostrarInfo();
		cout << "ID Credito Personal: " << id_credito_personal
			<< " | Destino Credito: " << destino_credito
			<< " | Seguro Desgravamen: " << (seguro_desgravamen ? "Si" : "No") << endl;
	}

	void solicitarCreditoPersonal(double monto) {
		cout << "Solicitando credito personal por: $" << monto << endl;
		cout << "Destino: " << destino_credito << endl;
		if (seguro_desgravamen) {
			cout << "Incluye seguro de desgravamen" << endl;
		}
	}
	//calcularCuotaMensual
	void pagarAdelantado() {
		cout << "Realizando pago adelantado al credito personal" << endl;
		double interesAhorrado = calcularInteres();
		cout << "Interes ahorrado estimado: $" << interesAhorrado << endl;
	}

	void desembolsar() {
		cout << "Desembolsando CREDITO PERSONAL" << endl;
		cout << "Destino: " << destino_credito << endl;
		Credito<string, double>::desembolsar();
	}


};
