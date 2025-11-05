#pragma once
#include <iostream>
#include <string>
#include"Servicios.h"
using namespace std;

template <typename T1, typename T2>
class Credito : public Servicios<string, double> {
private:
    T1 id_credito;      //string
    T2 monto_prestamo;  //double
    int plazo_meses;        //int
    T2 tasa_interes;    //double
    T2 saldo_pendiente; //double

    string generarID() {
        static int contador = 1;
        return "CRD-" + to_string(contador++);
	}

    // Calcular cuota mensual usando fórmula de amortización
    T2 calcularCuotaMensual() const {
        if (plazo_meses <= 0 || tasa_interes <= 0) return monto_prestamo;

        // Fórmula: Cuota = P * (r * (1 + r)^n) / ((1 + r)^n - 1)
        T2 tasa_mensual = tasa_interes / 12.0;
        T2 factor = pow(1 + tasa_mensual, plazo_meses);
        return monto_prestamo * (tasa_mensual * factor) / (factor - 1);
    }


public:
    // Constructor igual que Seguro
    Credito(T1 n_cuenta, T1 t, T1 f_a, T2 monto_prestamo, int plazo_meses, T2 tasa_interes): Servicios<string, double>(n_cuenta, t, f_a),monto_prestamo(monto_prestamo),plazo_meses(plazo_meses),tasa_interes(tasa_interes) {
        id_credito = generarID();
        saldo_pendiente = monto_prestamo;
    }
    // Getters (igual estructura que Seguro)
    T1 getIdCredito() { return id_credito; }
    T2 getMontoPrestamo() { return monto_prestamo; }
    int getPlazoMeses() { return plazo_meses; }
    T2 getTasaInteres() { return tasa_interes; }
    T2 getSaldoPendiente() { return saldo_pendiente; }
    // Setters (igual estructura que Seguro)
    void setMontoPrestamo(T2 monto_prestamo) { this->monto_prestamo = monto_prestamo; }
    void setPlazoMeses(int plazo_meses) { this->plazo_meses = plazo_meses; }
    void setTasaInteres(T2 tasa_interes) { this->tasa_interes = tasa_interes; }
    
    double consultarSaldo() const  {
        return saldo_pendiente;
    }
    // TUS MÉTODOS ESPECÍFICOS (manteniendo tu lógica)
     void desembolsar() {
        cout << "Desembolsando credito por: $" << monto_prestamo << endl;
        saldo_pendiente = monto_prestamo;
    }

    virtual void pagarCuota(double monto) {
        if (monto <= saldo_pendiente) {
            saldo_pendiente -= monto;
            cout << "Pago realizado. Saldo pendiente: $" << saldo_pendiente << endl;
        }
        else {
            cout << "Monto excede el saldo pendiente" << endl;
        }
    }

    virtual double calcularInteres() const {
        return saldo_pendiente * tasa_interes;
    }
    virtual void generarCronogramaPagos() const {
        cout << "=== CRONOGRAMA DE PAGOS ===" << endl;
        cout << "Monto total: $" << monto_prestamo << endl;
        cout << "Plazo: " << plazo_meses << " meses" << endl;
        cout << "Tasa de interes: " << (tasa_interes * 100) << "%" << endl;

        double cuota = monto_prestamo / plazo_meses;
        double saldo = monto_prestamo;

        for (int i = 1; i <= plazo_meses; i++) {
            double interes = saldo * tasa_interes;
            double amortizacion = cuota - interes;
            saldo -= amortizacion;

            cout << "Mes " << i << ": Cuota $" << cuota
                << " (Interes: $" << interes << ", Amortizacion: $" << amortizacion << ")" << endl;
        }
    }

    // Método mostrarInfo como en Seguro
    void mostrarInfo() const {
        cout << "ID Credito: " << id_credito
            << " | Monto: $" << monto_prestamo
            << " | Plazo: " << plazo_meses << " meses"
            << " | Tasa: " << (tasa_interes * 100) << "%"
            << " | Saldo Pendiente: $" << saldo_pendiente << endl;
    }

};