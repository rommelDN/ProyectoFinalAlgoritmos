#pragma once
#include <iostream>
#include <string>
#include <cmath> 
#include "Servicios.h"

using namespace std;

template <typename T1, typename T2>
class Credito : public Servicios<string, double> {
private:
    T1 id_credito;      // string
    T2 monto_prestamo;  // double
    int plazo_meses;    // int
    T2 tasa_interes;    // double (Ej: 0.05 para 5%)
    T2 saldo_pendiente; // double

    string generarID() {
        static int contador = 1;
        return "CRD-" + to_string(contador++);
    }

public:
    // Constructor
    Credito(T1 n_cuenta, T1 t, T1 f_a, T2 monto_prestamo, int plazo_meses, T2 tasa_interes)
        : Servicios<string, double>(n_cuenta, t, f_a),
        monto_prestamo(monto_prestamo),
        plazo_meses(plazo_meses),
        tasa_interes(tasa_interes) {
        id_credito = generarID();
        saldo_pendiente = monto_prestamo;
    }

    // Getters
    T1 getIdCredito() { return id_credito; }
    T2 getMontoPrestamo() { return monto_prestamo; }
    int getPlazoMeses() { return plazo_meses; }
    T2 getTasaInteres() { return tasa_interes; }
    T2 getSaldoPendiente() { return saldo_pendiente; }

    // Setters
    void setMontoPrestamo(T2 monto) { this->monto_prestamo = monto; }
    void setPlazoMeses(int plazo) { this->plazo_meses = plazo; }
    void setTasaInteres(T2 tasa) { this->tasa_interes = tasa; }

    //metodo consultar saldo(heredado)
    double consultarSaldo() const {
        return saldo_pendiente;
    }



    // 1. Calcular Cuota Mensual (Sistema Francés)
    virtual double calcularCuotaMensual() const {
        // Fórmula: R = P * [i * (1+i)^n] / [(1+i)^n - 1]
        double i = tasa_interes; // Tasa mensual (Ej: 0.02)

        // Validación para evitar división por cero si la tasa es 0
        if (i == 0) return monto_prestamo / plazo_meses;

        double numerador = i * pow(1 + i, plazo_meses);
        double denominador = pow(1 + i, plazo_meses) - 1;

        return monto_prestamo * (numerador / denominador);
    }

    //generar Cronograma
    virtual void generarCronogramaPagos() const {
        cout << "\n    CRONOGRAMA DE PAGOS    " << endl;
        cout << "Monto: $" << monto_prestamo << " | Plazo: " << plazo_meses << " meses" << endl;
        cout << "Tasa mensual: " << (tasa_interes * 100) << "%" << endl;

        double cuotaFija = calcularCuotaMensual();
        double saldoTemp = monto_prestamo;

        cout << "--------------------------------------------------------------" << endl;
        cout << "Mes\t| Cuota\t\t| Interes\t| Capital\t| Saldo" << endl;
        cout << "--------------------------------------------------------------" << endl;

        for (int mes = 1; mes <= plazo_meses; mes++) {
            double interes = saldoTemp * tasa_interes;
            double amortizacionCapital = cuotaFija - interes;
            saldoTemp -= amortizacionCapital;

            if (saldoTemp < 0) saldoTemp = 0; // Ajuste por decimales

            cout << mes << "\t| " << fixed << setprecision(2) << cuotaFija
                << "\t| " << interes
                << "\t\t| " << amortizacionCapital
                << "\t\t| " << saldoTemp << endl;
        }
        cout << "--------------------------------------------------------------" << endl;
    }

    // 3. Desembolsar
    virtual void desembolsar() {
        cout << "Desembolsando credito por: $" << monto_prestamo << endl;
        saldo_pendiente = monto_prestamo;
    }

    // 4. Pagar Cuota
    virtual void pagarCuota(double monto) {
        if (monto <= saldo_pendiente + 1.0) {
            saldo_pendiente -= monto;
            if (saldo_pendiente < 0) saldo_pendiente = 0;
            cout << "Pago de $" << monto << " realizado con exito." << endl;
            cout << "Nuevo saldo pendiente: $" << saldo_pendiente << endl;
        }
        else {
            cout << "Error: El monto excede el saldo pendiente ($" << saldo_pendiente << ")" << endl;
        }
    }

    virtual double calcularInteres() const {
        return saldo_pendiente * tasa_interes;
    }

    void mostrarInfo() const {
        cout << "ID Credito: " << id_credito
            << " | Monto Original: $" << monto_prestamo
            << " | Plazo: " << plazo_meses << " meses"
            << " | Tasa: " << (tasa_interes * 100) << "%"
            << " | Saldo Pendiente: $" << saldo_pendiente << endl;
    }
};
