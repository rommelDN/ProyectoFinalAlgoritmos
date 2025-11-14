#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>


using namespace std;

class HashEntidad {
private:
	string key;
	int valor;
public:
	HashEntidad(string key, int valor) :key(key), valor(valor) {}
	string getKey() { return key; };
	int getValue() { return valor; };
	void setValue(int e) { valor = e; };
};


class HashTable {
private:
	HashEntidad** table;
	int TABLE_SIZE;
	int numElementos;
	int hashFunction(const string& key)const {
		int hash = 0;
		for (char c : key) hash = (hash * 37 + int(c)) % TABLE_SIZE;
		return hash;
	}
public:
	HashTable(int size) :TABLE_SIZE(size), numElementos(0) {
		table = new HashEntidad * [TABLE_SIZE];
		for (int i = 0;i < TABLE_SIZE;i++) table[i] = nullptr;
	}
	~HashTable() {
		for (int i = 0;i < TABLE_SIZE;i++) {
			if (table[i] != nullptr)delete table[i];
		}
		delete[] table;
	}
	void insertar(string key, int value) {
		int index = hashFunction(key);
		int original = index, step = 1;
		while (table[index] != nullptr && table[index]->getKey() != key) {
			index = (original + step) % TABLE_SIZE;
			step++;
		}
		if (table[index] != nullptr) table[index]->setValue(value);
		else {
			table[index] = new HashEntidad(key, value);
			numElementos++;
		}
	}
	int buscar(string key)const {
		int index = hashFunction(key);
		int original = index, step = 1;
		while (table[index] != nullptr) {
			if (table[index]->getKey() == key) return table[index]->getValue();
			index = (original + step) % TABLE_SIZE;
			step++;
		}
	}
	void mostrar()const {
		cout << "\n=== TABLE HASH ===\n";
		for (int i = 0;i < TABLE_SIZE;i++) {
			if (table[i] != nullptr) {
				cout << "[" << i << "]" << table[i]->getKey() << "[" << i << "]" << table[i]->getValue() << endl;
			}
			else cout << "[" << i << "] ---\n";
		}
	};

};