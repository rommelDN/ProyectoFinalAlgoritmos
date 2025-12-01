#pragma once
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

// Nodo del grafo que representa un beneficiario
template<typename T1, typename T2>
struct NodoBeneficiario {
    string id_beneficiario;
    string nombre;
    T2 porcentaje;

    // Constructor por defecto (necesario para map)
    NodoBeneficiario() : id_beneficiario(""), nombre(""), porcentaje(0) {}

    // Constructor con parámetros
    NodoBeneficiario(string id, string n, T2 p)
        : id_beneficiario(id), nombre(n), porcentaje(p) {
    }
};

// Arista que representa una relación entre beneficiarios
template<typename T2>
struct AristaBeneficiario {
    string destino;
    T2 peso; // Puede representar porcentaje compartido, prioridad, etc.
    string tipo_relacion; // "DEPENDIENTE", "FAMILIAR", "SUSTITUTO", etc.

    // Constructor por defecto
    AristaBeneficiario() : destino(""), peso(0), tipo_relacion("") {}

    // Constructor con parámetros
    AristaBeneficiario(string dest, T2 p, string tipo)
        : destino(dest), peso(p), tipo_relacion(tipo) {
    }
};

// Clase Grafo para gestionar red de beneficiarios
template<typename T1, typename T2>
class GrafoBeneficiarios {
private:
    // Mapa de adyacencia: cada beneficiario tiene una lista de conexiones
    map<string, vector<AristaBeneficiario<T2>>> adyacencias;
    map<string, NodoBeneficiario<T1, T2>> nodos;

public:
    GrafoBeneficiarios() {}

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Agregar un beneficiario al grafo
    void agregarBeneficiario(const string& id, const string& nombre, T2 porcentaje) {
        if (nodos.find(id) == nodos.end()) {
            nodos[id] = NodoBeneficiario<T1, T2>(id, nombre, porcentaje);
            adyacencias[id] = vector<AristaBeneficiario<T2>>();
            cout << "Beneficiario '" << nombre << "' agregado al grafo.\n";
        }
        else {
            cout << "El beneficiario ya existe en el grafo.\n";
        }
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Crear relación entre dos beneficiarios
    void crearRelacion(const string& origen, const string& destino, T2 peso, const string& tipo) {
        if (nodos.find(origen) == nodos.end() || nodos.find(destino) == nodos.end()) {
            cout << "Error: Uno o ambos beneficiarios no existen.\n";
            return;
        }

        adyacencias[origen].push_back(AristaBeneficiario<T2>(destino, peso, tipo));
        cout << "Relación creada: " << nodos[origen].nombre
            << " -> " << nodos[destino].nombre
            << " [" << tipo << ", peso: " << peso << "]\n";
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Mostrar el grafo completo
    void mostrarGrafo() const {
        if (nodos.empty()) {
            cout << "El grafo está vacío.\n";
            return;
        }

        cout << "\n===== RED DE BENEFICIARIOS =====\n";
        for (const auto& par : adyacencias) {
            const string& id = par.first;
            cout << "\n" << nodos.at(id).nombre
                << " (ID: " << id
                << ", " << nodos.at(id).porcentaje << "%)\n";

            if (par.second.empty()) {
                cout << "  L__ Sin relaciones\n";
            }
            else {
                for (size_t i = 0; i < par.second.size(); i++) {
                    const auto& arista = par.second[i];
                    cout << "  " << (i == par.second.size() - 1 ? "L" : "I-")
                        << "-- " << nodos.at(arista.destino).nombre
                        << " [" << arista.tipo_relacion
                        << ", peso: " << arista.peso << "]\n";
                }
            }
        }
    }

    

    bool estaVacio() const {
        return nodos.empty();
    }

    
};