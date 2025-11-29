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

    // BFS: Encontrar beneficiarios conectados desde un nodo
    void beneficiariosConectados(const string& id_inicio) const {
        if (nodos.find(id_inicio) == nodos.end()) {
            cout << "Beneficiario no encontrado.\n";
            return;
        }

        set<string> visitados;
        queue<string> cola;

        cola.push(id_inicio);
        visitados.insert(id_inicio);

        cout << "\nBeneficiarios conectados a " << nodos.at(id_inicio).nombre << ":\n";

        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();

            if (actual != id_inicio) {
                cout << "  - " << nodos.at(actual).nombre
                    << " (" << nodos.at(actual).porcentaje << "%)\n";
            }

            for (const auto& arista : adyacencias.at(actual)) {
                if (visitados.find(arista.destino) == visitados.end()) {
                    cola.push(arista.destino);
                    visitados.insert(arista.destino);
                }
            }
        }
    }

    // DFS: Detectar ciclos (posibles conflictos de interés)
    bool detectarCiclos() const {
        set<string> visitados;
        set<string> enProceso;

        for (const auto& par : nodos) {
            if (visitados.find(par.first) == visitados.end()) {
                if (dfsDetectarCiclos(par.first, visitados, enProceso)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Encontrar beneficiarios con mayor influencia (más conexiones)
    void beneficiariosMasInfluyentes(int top = 3) const {
        vector<pair<string, int>> influencia;

        for (const auto& par : adyacencias) {
            influencia.push_back({ par.first, par.second.size() });
        }

        sort(influencia.begin(), influencia.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second;
            });

        cout << "\n===== BENEFICIARIOS MÁS INFLUYENTES =====\n";
        for (int i = 0; i < min(top, (int)influencia.size()); i++) {
            cout << (i + 1) << ". " << nodos.at(influencia[i].first).nombre
                << " - " << influencia[i].second << " conexiones\n";
        }
    }

    // Calcular distribución acumulada de porcentajes en una cadena
    T2 calcularDistribucionAcumulada(const string& id_inicio) const {
        if (nodos.find(id_inicio) == nodos.end()) {
            return 0;
        }

        set<string> visitados;
        return dfsCalcularDistribucion(id_inicio, visitados);
    }

    // Validar que la suma de porcentajes no exceda 100%
    bool validarDistribucion() const {
        T2 suma_total = 0;
        for (const auto& par : nodos) {
            suma_total += par.second.porcentaje;
        }

        cout << "\nDistribución total: " << suma_total << "%\n";
        if (suma_total > 100) {
            cout << " ADVERTENCIA: La distribución excede el 100%\n";
            return false;
        }
        else if (suma_total < 100) {
            cout << "  Porcentaje no distribuido: " << (100 - suma_total) << "%\n";
        }
        else {
            cout << "Distribución válida\n";
        }
        return true;
    }

    // Encontrar beneficiarios sustitutos (sin conexiones entrantes)
    void encontrarBeneficiariosPrincipales() const {
        set<string> conEntrantes;

        for (const auto& par : adyacencias) {
            for (const auto& arista : par.second) {
                conEntrantes.insert(arista.destino);
            }
        }

        cout << "\n===== BENEFICIARIOS PRINCIPALES =====\n";
        cout << "(Sin dependencias de otros)\n";
        for (const auto& par : nodos) {
            if (conEntrantes.find(par.first) == conEntrantes.end()) {
                cout << "  . " << par.second.nombre
                    << " (" << par.second.porcentaje << "%)\n";
            }
        }
    }

    bool estaVacio() const {
        return nodos.empty();
    }

private:
    // DFS auxiliar para detectar ciclos
    bool dfsDetectarCiclos(const string& actual, set<string>& visitados,
        set<string>& enProceso) const {
        visitados.insert(actual);
        enProceso.insert(actual);

        for (const auto& arista : adyacencias.at(actual)) {
            if (visitados.find(arista.destino) == visitados.end()) {
                if (dfsDetectarCiclos(arista.destino, visitados, enProceso)) {
                    return true;
                }
            }
            else if (enProceso.find(arista.destino) != enProceso.end()) {
                cout << "Ciclo detectado: conflicto de interés en la red\n";
                return true;
            }
        }

        enProceso.erase(actual);
        return false;
    }

    // DFS auxiliar para calcular distribución acumulada
    T2 dfsCalcularDistribucion(const string& actual, set<string>& visitados) const {
        visitados.insert(actual);
        T2 suma = nodos.at(actual).porcentaje;

        for (const auto& arista : adyacencias.at(actual)) {
            if (visitados.find(arista.destino) == visitados.end()) {
                suma += dfsCalcularDistribucion(arista.destino, visitados);
            }
        }

        return suma;
    }
};