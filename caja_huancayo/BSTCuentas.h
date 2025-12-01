#pragma once
#include <iostream>
#include <string>
#include "ArbolBinarioBusqueda.h"
#include "Cuentas.h"
#include "HashTable.h"
using namespace std;

ArbolBB<Cuenta<string, double>>* arbolBST = nullptr;

void inicializarBST(HashTable<Cuenta<string, double>>& tablaCuentas) {
    auto procesador = [](Cuenta<string, double> c) {
        c.mostrar();
        };

    // Comparador: ordenar por límite de retiro
    auto comparador = [](Cuenta<string, double> a, Cuenta<string, double> b) -> int {
        double limiteA = a.getLimiteRetiro();
        double limiteB = b.getLimiteRetiro();
        if (limiteA < limiteB) return -1;
        if (limiteA > limiteB) return 1;
        return 0;
        };

    // Extractor: para visualización del árbol
    auto extractor = [](const Cuenta<string, double>& c) -> int {
        return static_cast<int>(c.getLimiteRetiro());
        };

    arbolBST = new ArbolBB<Cuenta<string, double>>(procesador, comparador, extractor);

    auto cuentas = tablaCuentas.toVector();
    for (const auto& cuenta : cuentas) {
        arbolBST->insertar(cuenta);
    }

    cout << "BST inicializado con " << cuentas.size() << " cuentas." << endl;
}

void mostrarCuentasOrdenadas(HashTable<Cuenta<string, double>>& tablaCuentas) {
    cout << "\n=== CUENTAS ORDENADAS POR LIMITE DE RETIRO (BST) ===" << endl;

    // Inicializar si es la primera vez
    if (arbolBST == nullptr) {
        inicializarBST(tablaCuentas);
    }

    // Mostrar en orden (ascendente por límite de retiro)
    arbolBST->enOrden();
}

void mostrarEstructuraBST(HashTable<Cuenta<string, double>>& tablaCuentas) {
    cout << "\n=== ESTRUCTURA DEL ARBOL BST ===" << endl;

    // Inicializar si es la primera vez
    if (arbolBST == nullptr) {
        inicializarBST(tablaCuentas);
    }

    // Mostrar estructura
    arbolBST->mostrar();

    cout << "\nEstadisticas:" << endl;
    cout << "Total de cuentas: " << arbolBST->cantidad() << endl;
    cout << "Altura del arbol: " << arbolBST->altura() << endl;
}