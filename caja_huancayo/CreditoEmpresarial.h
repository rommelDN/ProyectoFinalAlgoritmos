#pragma once
#include<iostream>
#include "Credito.h"
using namespace std;

template <typename T1, typename T2>
class CreditoEmpresarial : public Credito<string,double>{
private:
	T1 id_credito_empresarial; //string
    T1 nombre_empresa;         //string
    T1 ruc;                    //string
    T2 linea_credito;          //double

    string generarID() {
        static int contador = 1;
        return "CRE-" + to_string(contador++);
    };
public:
    CreditoEmpresarial(T1 n_cuenta, T1 t, T1 f_a, T2 monto_prestamo, int plazo_meses, T2 tasa_interes,
                       T1 nombre_empresa, T1 ruc, T2 linea_credito)
        : Credito<string, double>(n_cuenta, t, f_a, monto_prestamo, plazo_meses, tasa_interes),
        nombre_empresa(nombre_empresa), ruc(ruc), linea_credito(linea_credito) {
        id_credito_empresarial = generarID();
    }
	// Getters
	T1 getIdCreditoEmpresarial() { return id_credito_empresarial; }
	T1 getNombreEmpresa() { return nombre_empresa; }
	T1 getRUC() { return ruc; }
	T2 getLineaCredito() { return linea_credito; }
	// Setters
	void setNombreEmpresa(T1 nombre_empresa) { this->nombre_empresa = nombre_empresa; }
	void setRUC(T1 ruc) { this->ruc = ruc; }
	void setLineaCredito(T2 linea_credito) { this->linea_credito = linea_credito; }

    void solicitarCreditoEmpresarial() {
        cout << "=== SOLICITUD CRÉDITO EMPRESARIAL ===" << endl;
        cout << "Empresa: " << this->getNombreEmpresa() << endl;
        cout << "RUC: " << this->getRUC() << endl;
        cout << "Línea de crédito disponible: $" << this->getLineaCredito() << endl;
        cout << "Monto solicitado: $" << this->getMontoPrestamo() << endl; 
        cout << "Plazo: " << this->getPlazoMeses() << " meses" << endl;    
        cout << "Tasa: " << (this->getTasaInteres() * 100) << "%" << endl; 
    }

};
