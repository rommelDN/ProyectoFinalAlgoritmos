#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

template<typename T, typename Comparar>
int particion(vector<T>& arr, int abajo, int arriba, Comparar comp) {
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
}
template<typename T, typename Comparar>
void quicksort(vector<T>& arr, int abajo, int arriba, Comparar comp) {
    if (abajo < arriba) {
        int pi = particion(arr, abajo, arriba, comp);
        quicksort(arr, abajo, pi - 1, comp);
        quicksort(arr, pi + 1, arriba, comp);
    }
}