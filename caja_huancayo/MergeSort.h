#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

template<typename T, typename Comparar>
void merge(vector<T>& arr, int izq, int mid, int der, Comparar comp) {
	vector<T> temp;
	int i = izq, j = mid + 1;
	while (i <= mid && j <= der) {
		if(comp(arr[i], arr[j]))temp.push_back(arr[i++]);
		else temp.push_back(arr[j++]);
	}
	while (i <= mid) temp.push_back(arr[i++]);
	while (j <= der) temp.push_back(arr[j++]);
	for (int k = izq; k <= der; k++) {
		arr[k] = temp[k - izq];
	};
}

template<typename T, typename Comparar>
void mergeSort(vector<T>& arr, int izq, int der, Comparar comp) {
	if (izq >= der)return;
	int mid = izq + (der - izq) / 2;
	mergeSort(arr, izq, mid, comp);
	mergeSort(arr, mid + 1, der, comp);
	merge(arr, izq, mid, der, comp);
};