#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include "Cuentas.h"
#include "ListaEnlazada.h"
#include "HashTable.h"
using namespace std;
template<typename T1, typename T2>
HashTable<Servicios<string, double>>* Cuenta<T1, T2>::tablaServiciosGlobal = nullptr;