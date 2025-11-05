#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include "Tarjetas.h"
using namespace std;

template <typename T1,typename T2>
class TarjetaDebito : public Tarjetas<string> {
private:
	T1 id_debito;
	T2 limite_diario_retiro;

	string generarID() {
		static int contador = 1;
		return "DBT-" + to_string(contador++);
	}


public:
	TarjetaDebito(T1 n_cuenta, T1 t, T1 f_a, T1 n_tarjeta, T1 f_emision, T1 f_vencimiento, T1 cvv, T2 limite_retiro)
		: Tarjetas<string>(n_cuenta, t, f_a, n_tarjeta, f_emision, f_vencimiento, cvv), limite_diario_retiro(limite_retiro) {
		id_debito = generarID();
	}

	//getters
	T1 getIdDebito() { return id_debito; }
	T1 getNumCuentaBancaria() { return num_cuenta_bancaria; }
	T2 getLimiteDiarioRetiro() { return limite_diario_retiro; }
	//setters
	void setNumCuentaBancaria(T1 n_cuenta_bancaria) { this->num_cuenta_bancaria = n_cuenta_bancaria; }
	void setLimiteDiarioRetiro(T2 limite_retiro) { this->limite_diario_retiro = limite_retiro; }
	void mostrarInfo() const {
		Tarjetas<string>::mostrarInfo();
		cout << "ID Debito: " << id_debito
			<< " | Num Cuenta Bancaria: " << num_cuenta_bancaria
			<< " | Limite Diario Retiro: $" << limite_diario_retiro << endl;
	}

	void retirar(double monto)  {
		
	}

	void depositar(double monto) {
		
	}

	void consultarSaldo() const {
		cout << "Saldo disponible en cuenta " << this->getNumCuenta() << ": $";
		Tarjetas<string>::consultarSaldo();
	}

	void listarMovimientos() const {
		
	}
	
};