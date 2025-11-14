#pragma once
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T, typename Comparar>
int particionQuickSelect(vector<T>& arr, int abajo, int arriba, Comparar comp) {
    T pivote = arr[arriba];
    int i = abajo - 1;
    for (int j = abajo; j < arriba; j++) {
        if (comp(arr[j], pivote)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[arriba]);
    return i + 1;
};
template<typename T, typename Comparar>
T quickselect(vector<T>& arr, int abajo, int arriba, int k, Comparar comp) {
    if (abajo == arriba) return arr[abajo];
    int pi = particionQuickSelect(arr, abajo, arriba, comp);
    if (k == pi) return arr[pi]; 
    else if (k < pi) return quickselect(arr, abajo, pi - 1, k, comp);
    else return quickselect(arr, pi + 1, arriba, k, comp);
}

