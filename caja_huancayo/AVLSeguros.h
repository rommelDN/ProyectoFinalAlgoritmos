#pragma once
#include <iostream>
#include <string>
#include "ArbolBinarioVL.h"
#include "Seguros.h"
#include "HashTable.h"
using namespace std;

struct SeguroComparable {
    string id_seguro;
    string tipo_seguro;
    double prima_mensual;
    double monto_cobertura;
    double meses_cobertura;
    string num_cuenta;

    // Constructor
    SeguroComparable(const Seguros<string, double>& s) {
        id_seguro = s.getIdSeguro();
        tipo_seguro = s.getTipoSeguro();
        prima_mensual = s.getPrimaMensual();
        monto_cobertura = s.getMontoCobertura();
        meses_cobertura = s.getMesesCobertura();
        num_cuenta = s.getNumCuenta();
    }

    // Operadores de comparación (por prima mensual)
    bool operator<(const SeguroComparable& otro) const {
        return prima_mensual < otro.prima_mensual;
    }

    bool operator>(const SeguroComparable& otro) const {
        return prima_mensual > otro.prima_mensual;
    }

    bool operator==(const SeguroComparable& otro) const {
        return id_seguro == otro.id_seguro;
    }

    // Método para mostrar
    void mostrar() const {
        cout << "ID Seguro: " << id_seguro
            << " | Tipo Seguro: " << tipo_seguro
            << " | Prima Mensual: $" << prima_mensual
            << " | Monto Cobertura: $" << monto_cobertura
            << " | Meses Cobertura: " << meses_cobertura << endl;
    }

    // Sobrecarga del operador <<
    friend ostream& operator<<(ostream& os, const SeguroComparable& sc) {
        sc.mostrar();
        return os;
    }
};

ArbolAVL<SeguroComparable>* arbolAVL_Seguros = nullptr;

void inicializarAVL_Seguros(HashTable<Seguros<string, double>>& tablaSeguros) {
    auto procesador = [](SeguroComparable sc) {
        sc.mostrar();
        };

    arbolAVL_Seguros = new ArbolAVL<SeguroComparable>(procesador);

    auto seguros = tablaSeguros.toVector();
    for (const auto& seguro : seguros) {
        SeguroComparable wrapper(seguro);
        arbolAVL_Seguros->insertar(wrapper);
    }

    cout << "AVL inicializado con " << seguros.size() << " seguros." << endl;
}

void mostrarSegurosOrdenados_AVL(HashTable<Seguros<string, double>>& tablaSeguros) {
    cout << "\n=== SEGUROS ORDENADOS POR PRIMA MENSUAL (AVL) ===" << endl;

    if (arbolAVL_Seguros == nullptr) {
        inicializarAVL_Seguros(tablaSeguros);
    }

    arbolAVL_Seguros->enOrden();
}

void mostrarEstructuraAVL_Seguros(HashTable<Seguros<string, double>>& tablaSeguros) {
    cout << "\n=== ESTRUCTURA DEL ARBOL AVL ===" << endl;

    if (arbolAVL_Seguros == nullptr) {
        inicializarAVL_Seguros(tablaSeguros);
    }

    arbolAVL_Seguros->mostrar();

    cout << "\nEstadisticas:" << endl;
    cout << "Total de seguros: " << arbolAVL_Seguros->cantidad() << endl;
    cout << "Altura del arbol: " << arbolAVL_Seguros->altura() << endl;
    cout << "El arbol AVL se auto-balancea!" << endl;
}


void limpiarAVL_Seguros() {
    if (arbolAVL_Seguros != nullptr) {
        delete arbolAVL_Seguros;
        arbolAVL_Seguros = nullptr;
    }
}