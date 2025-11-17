 #pragma once
#include <string>
#include<iostream>
#include "servicios.h"
#include "ListaEnlazada.h"
#include "Pila.h"
#include "MetaAhorro.h"
#include "HashTable.h"
using namespace std;
template <typename T1, typename T2>
class Cuenta : public Servicios<string, double> {
private:
	T1 id_cuenta;		//String
	T1 tipo_cuenta;		//String: "AHORRO"
	T2 tasa_interes;	//double
	T2 limite_retiro;	//double
	T2 ahorroObjetivo;	//double
	Pila<MetaAhorro<string, double>>* metasAhorro;

	string generarID() {
		static int contador = 1;
		return "CTA-" + to_string(contador++);
	}

	//LISTA ESTÁTICA COMPARTIDA para todos los objetos Cuenta
	static HashTable<Servicios<string, double>>* tablaServiciosGlobal;

public:
	Cuenta(T1 n_cuenta, T1 t, T1 f_a, T2 tasa_int, T2 limite_ret, T2 ahorro_obj)
		: Servicios<string, double>(n_cuenta, t, f_a), tasa_interes(tasa_int),
		limite_retiro(limite_ret), ahorroObjetivo(ahorro_obj) {
		id_cuenta = generarID();
		tipo_cuenta = "AHORRO";
		metasAhorro = new Pila<MetaAhorro<string, double>>();
		if (tablaServiciosGlobal != nullptr) {
			tablaServiciosGlobal->insertar(n_cuenta, *this);
		}
	}

	static void setTablaServiciosGlobal(HashTable<Servicios<string, double>>& tabla) {
		tablaServiciosGlobal = &tabla;
	}

    //getters
	T1 getIdCuenta() const{ return id_cuenta; }
	T1 getTipoCuenta()const { return tipo_cuenta; }
	T2 getTasaInteres()const { return tasa_interes; }
	T2 getLimiteRetiro()const { return limite_retiro; }
	T2 getAhorroObjetivo()const { return ahorroObjetivo; }
    //setters
	void setTasaInteres(T2 tasa) { tasa_interes = tasa; }
	void setLimiteRetiro(T2 limite) { limite_retiro = limite; }
    void setAhorroObjetivo(T2 obj) { ahorroObjetivo = obj; }

    void depositar(T1 monto) {    
    }
    
	void retirar(T1 monto) {
    }

	void verificarMetasAhorro() {
		if (!metasAhorro->estaVacia()) {
			MetaAhorro<string, double> metaActual = metasAhorro->getTope();
			double progreso = (this->getSaldo() / metaActual.getMontoObjetivo()) * 100;

			if (progreso < metaActual.calcularProgreso()) {
				cout << "Atención: El retiro ha reducido tu progreso hacia la meta de ahorro" << std::endl;
				cout << "Progreso actual: " << progreso << "%" << endl;
			}
		}
	}

    T2 getLimiteRetiroDisponible() {
		return std::min(limite_retiro, this->getSaldo());
    }

	void establecerMetaAhorro(double objetivo, string fechaObjetivo) {
		if (objetivo <= 0) {
			cout << "Error: El objetivo debe ser mayor a 0" << endl;
			return;
		}

		MetaAhorro<string, double> nuevaMeta(objetivo, 0.0, fechaObjetivo);
		metasAhorro->apilar(nuevaMeta);
		ahorroObjetivo = objetivo;

		cout << "NUEVA META ESTABLECIDA:" << endl;
		cout << "Objetivo: $" << objetivo << endl;
		cout << "Fecha límite: " << fechaObjetivo << endl;
		cout << "Meta apilada correctamente" << endl;
	}

    void consultarMetaActual()  {
        if (metasAhorro->estaVacia()) {
            cout << "No hay metas de ahorro establecidas" << endl;
            return;
        }

        MetaAhorro<std::string, double> metaActual = metasAhorro->getTope();
        cout << "META ACTUAL:" << endl;
        metaActual.mostrarProgreso();

        double progreso = (Servicios<string, double>::getSaldo() / metaActual.getMontoObjetivo()) * 100;
        cout << "Progreso real: " << fixed << setprecision(1) << progreso << "%" << std::endl;

        if (metaActual.metaCumplida()) {
            cout << "¡META CUMPLIDA!" << endl;
        }
    }

    // Y en completarMetaActual:
	bool completarMetaActual() {
		if (metasAhorro->estaVacia()) {
			cout << "No hay metas para completar" << endl;
			return false;
		}

		MetaAhorro<string, double> metaActual = metasAhorro->getTope();

		if (this->getSaldo() >= metaActual.getMontoObjetivo()) {
			MetaAhorro<string, double> metaCompletada = metasAhorro->desapilar();
			cout << "¡META COMPLETADA!" << endl;
			cout << "Objetivo: $" << metaCompletada.getMontoObjetivo() << endl;
			cout << "Logrado: $" << this->getSaldo() << endl;

			// Actualizar ahorro objetivo si hay otra meta
			if (!metasAhorro->estaVacia()) {
				ahorroObjetivo = metasAhorro->getTope().getMontoObjetivo();
				std::cout << "Nueva meta activa: $" << ahorroObjetivo << std::endl;
			}
			else {
				ahorroObjetivo = 0.0;
				std::cout << "No hay más metas pendientes" << std::endl;
			}

			return true;
		}
		else {
			std::cout << "Aún no se cumple la meta actual" << std::endl;
			std::cout << "Faltan: $" << (metaActual.getMontoObjetivo() - this->getSaldo()) << std::endl;
			return false;
		}
	}

	bool cancelarMetaActual() {
		if (metasAhorro->estaVacia()) {
			cout << "No hay metas para cancelar" << endl;
			return false;
		}

		MetaAhorro<string, double> metaCancelada = metasAhorro->desapilar();
		cout << "META CANCELADA:" << endl;
		cout << "Objetivo: $" << metaCancelada.getMontoObjetivo() << endl;
		cout << "Fecha: " << metaCancelada.getFechaObjetivo() << endl;

		// Actualizar ahorro objetivo si hay otra meta
		if (!metasAhorro->estaVacia()) {
			ahorroObjetivo = metasAhorro->getTope().getMontoObjetivo();
			cout << "Nueva meta activa: $" << ahorroObjetivo << endl;
		}
		else {
			ahorroObjetivo = 0.0;
			cout << "No hay metas activas" << endl;
		}

		return true;
	}

	void mostrar() {
		//Servicios<string, double>::mostrarInfo();
		cout << "ID Cuenta: " << id_cuenta
			<< " | Tipo Cuenta: " << tipo_cuenta
			<< " | Tasa Interes: " << tasa_interes << "%"
			<< " | Limite Retiro: $" << limite_retiro
			<< " | Ahorro Objetivo: $" << ahorroObjetivo << endl;
	}

	// Sobrecarga del operador << para poder imprimir
	friend ostream& operator<<(ostream& os, const Cuenta& e) {
		os << e.getIdCuenta() << "(" << " Tipo Cuenta " << e.getTipoCuenta() << "| Tasa de Interes: " << e.getTasaInteres() << " | Limite x Retiro: " << e.getLimiteRetiro()<< ")";
		return os;
	}

};