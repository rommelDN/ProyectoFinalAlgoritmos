#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

template <typename T>
vector<int> binarySearch(vector<T>& arr, T x, int abajo, int arriba) {
	if(abajo > arriba) return {};
	int mid = abajo + (arriba - abajo) / 2;
	if (arr[mid] == x) {
		vector<int> indices;
		auto izq = binarySearch(arr, x, abajo, mid - 1);
		auto der = binarySearch(arr, x, mid + 1, arriba);
		indices.insert(indices.end(), izq.begin(), izq.end());
		indices.insert(indices.end(), der.begin(),der.end());
		return indices;
	}
	if (arr[mid] < x) return binarySearch(arr,x,mid+1,arriba);
	else return binarySearch(arr, x, abajo, mid - 1);
};