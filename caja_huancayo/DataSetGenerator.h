#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "HashTable.h"
using namespace std;
template <typename T>
class DataSetGenerator {
public:
    
    using Extractor = function<string(const T&)>;

    static void listar(
        const vector<string>& columnas,
        const vector<Extractor>& extractores,
        HashTable<T>& tabla
    ) {
       
        for (const string& col : columnas)
            cout << col << "\t";
        cout << "\n----------------------------------------\n";

        
        tabla.forEach([&](const T& item) {
            for (auto& ex : extractores)
                cout << ex(item) << "\t";
            cout << "\n";
            });
    }
};
