#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "Servicios.h"
#include "Cliente.h"
using namespace std;
template <typename T>
class ServicioContratado : public Servicios<string, double>, public Cliente<string> {
private:
    T id_ser_contr;         //String
    //T id_servicio;       //String
    //T id_cliente;             //String
    T fecha_contratacion;  //String
    T estado;              //String    PENDIENTE - ACTIVO
    shared_ptr<Servicios<string,double>> servicio_ref;
    shared_ptr<Cliente<string>> cliente_ref;

    string generarID() {
        static int contador = 1;
        return "SRVC-" + to_string(contador++);
    }
public:
    ServicioContratado(T f, shared_ptr<Servicios<string, double>> s, shared_ptr<Cliente<string>> c):fecha_contratacion(f), servicio_ref(s),cliente_ref(c){
        id_ser_contr = generarID();
		estado = "PENDIENTE";
    }

    //getters
	T getID() const { return id_ser_contr; }
	T getFechaContratacion() const { return fecha_contratacion; }
    T getEstado() const { return estado; }
    shared_ptr<Servicios<string,double>> getServicioRef() const { return servicio_ref; }
    shared_ptr<Cliente<string>> getClienteRef() const { return cliente_ref; }
    //setters
    void setFechaContratacion(T f) { fecha_contratacion = f; }
    void setEstado(T e) { estado = e; }
    void mostrarInfo() const {
        cout << "ID Servicio Contratado: " << id_ser_contr
             << " | Fecha Contratacion: " << fecha_contratacion
             << " | Estado: " << estado << endl;
        cout << "-> Info del Servicio Contratado: " << endl;
        servicio_ref->mostrarInfo();
        cout << "-> Info del Cliente que contrato el servicio: " << endl;
        cliente_ref->mostrarInfo();
	}
    friend ostream& operator<<(ostream& os, const ServicioContratado& e) {
        os << "( "<<"|ID: " << e.getID()<<"| DNI: "<<e.getClienteRef()->getDNI() << "| CLIENTE: " << e.getClienteRef()->getNombre() << "| NUM_CUENTA: " << e.getServicioRef()->getNumCuenta() <<")";
        return os;
    }

	ServicioContratado() = default;
    
};