#pragma once
#include <string>
#include <iostream>
using namespace std;

template<typename T1, typename T2>
class MetaAhorro {
private: 
	T1 id_meta_ahorro;	//string
	T2 montoObjetivo;	//double
	T2 ahorradoActual;	//double
	T1 fechaObjetivo;	//string

	string generarID() {
		static int contador = 1;
		return "MAH-" + to_string(contador++);
	}
public:
	MetaAhorro(T2 montoObjetivo, T2 ahorradoActual, T1 fechaObjetivo): montoObjetivo(montoObjetivo), ahorradoActual(ahorradoActual), fechaObjetivo(fechaObjetivo) {
		id_meta_ahorro = generarID();
	}
	
	// Getters
	T1 getIdMetaAhorro() const { return id_meta_ahorro; }
	T2 getMontoObjetivo() const { return montoObjetivo; }
	T2 getAhorradoActual() const { return ahorradoActual; }
	T1 getFechaObjetivo() const { return fechaObjetivo; }
	// Setters
	void setMontoObjetivo(T2 monto) { montoObjetivo = monto; }
	void setAhorradoActual(T2 ahorrado) { ahorradoActual = ahorrado; }
	void setFechaObjetivo(T1 fecha) { fechaObjetivo = fecha; }
	void mostrarInfo() const {
		cout << "ID Meta Ahorro: " << id_meta_ahorro
			 << " | Monto Objetivo: " << montoObjetivo
			 << " | Ahorrado Actual: " << ahorradoActual
			 << " | Fecha Objetivo: " << fechaObjetivo << endl;
	}
	double calcularProgreso() const {
		return (ahorradoActual / montoObjetivo) * 100;
	}

	void mostrarProgreso() const {
		double progreso = calcularProgreso();
		std::cout << "Meta: $" << montoObjetivo << " para " << fechaObjetivo << std::endl;
		std::cout << "Ahorrado: $" << ahorradoActual << " (" << progreso << "%)" << std::endl;
	}

	bool metaCumplida() const {
		return ahorradoActual >= montoObjetivo;
	}
};