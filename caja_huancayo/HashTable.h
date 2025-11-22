#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
#include"ListaEnlazada.h"

using namespace std;
template<typename T>
class HashEntidad {
private:
	string key;
	T valor;
public:
	HashEntidad(string key, T valor) :key(key), valor(valor) {}
	string getKey() { return key; };
	T getValue() { return valor; };
	void setValue(T e) { valor = e; };

	T& getValueRef() { return valor; }
	const T& getValueRef() const { return valor; }

	void setValueRef(const T& e) { valor = e; }
};

template<typename T>
class HashTable {
private:
	HashEntidad<T>** table;
	int TABLE_SIZE;
	int numElementos;
	static HashEntidad<T>* TOMBSTONE;
	int hashFunction(const string& key)const {
		int hash = 0;
		for (char c : key) hash = (hash * 37 + int(c)) % TABLE_SIZE;
		return hash;
	}
	double loadFactor() const {
		return (double)numElementos / TABLE_SIZE;
	}
	void rehash() {
		int oldSize = TABLE_SIZE;
		TABLE_SIZE *= 2;
		HashEntidad<T>** oldTable = table;
		table = new HashEntidad<T>*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
		numElementos = 0;
		for (int i = 0; i < oldSize; i++) {
			if (oldTable[i] != nullptr && oldTable[i] != TOMBSTONE) {
				insertar(oldTable[i]->getKey(), oldTable[i]->getValue());
				delete oldTable[i];
			}
		}
		delete[] oldTable;
	}
public:
	HashTable(int size = 10) :TABLE_SIZE(size), numElementos(0) {
		table = new HashEntidad<T>*[TABLE_SIZE];
		for (int i = 0;i < TABLE_SIZE;i++) table[i] = nullptr;
	}
	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (table[i] != nullptr && table[i] != TOMBSTONE)
				delete table[i];
		}
		delete[] table;
	}
	void insertar(string key, T value) {

		if (loadFactor() > 0.7)rehash();
		int index = hashFunction(key);
		int original = index, step = 1;
		while (table[index] != nullptr && table[index] != TOMBSTONE && table[index]->getKey() != key) {
			index = (original + step) % TABLE_SIZE;
			step++;
		}
		if (table[index] != nullptr && table[index] != TOMBSTONE) {
			table[index]->setValue(value);
		}
		else {
			table[index] = new HashEntidad<T>(key, value);
			numElementos++;
		}
	}
	T* buscar(string key) const {
		int index = hashFunction(key);
		int original = index, step = 1;
		while (table[index] != nullptr) {
			if (table[index] != TOMBSTONE &&
				table[index]->getKey() == key) {
				return new T(table[index]->getValue()); // retorna copia
			}
			index = (original + step) % TABLE_SIZE;
			step++;
		}
		return nullptr;
	}
	bool eliminar(string key) {
		int index = hashFunction(key);
		int original = index, step = 1;
		while (table[index] != nullptr) {
			if (table[index] != TOMBSTONE &&
				table[index]->getKey() == key) {
				delete table[index];
				table[index] = TOMBSTONE;
				numElementos--;
				return true;
			}
			index = (original + step) % TABLE_SIZE;
			step++;
		}
		return false;
	}
	void mostrar() const {
		cout << "\n=== TABLE HASH ===\n";
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (table[i] == nullptr)
				cout << "[" << i << "] ---\n";
			else if (table[i] == TOMBSTONE)
				cout << "[" << i << "] <TOMBSTONE>\n";
			else
				cout << "[" << i << "] " << table[i]->getKey()
				<< " -> " << table[i]->getValue() << "\n";
		}
	}

	ListaEnlazada<T> toListaEnlazada() const {
		ListaEnlazada<T> lista;
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (table[i] != nullptr && table[i] != TOMBSTONE) {
				lista.agregarFinal(table[i]->getValue());
			}
		}
		return lista;
	}

	vector<T> toVector() const {
		vector<T> vec;
		vec.reserve(numElementos);

		for (int i = 0; i < TABLE_SIZE; i++) {
			if (table[i] != nullptr) {
				vec.push_back(table[i]->getValue());
			}
		}
		return vec;
	}

	void forEach(const function<void(const T&)>& callback) const {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (table[i] != nullptr && table[i] != TOMBSTONE) {
				callback(table[i]->getValue());
			}
		}
	}

	T* buscarRef(string key) {
		int index = hashFunction(key);
		int original = index, step = 1;

		while (table[index] != nullptr) {
			if (table[index] != TOMBSTONE &&
				table[index]->getKey() == key) {

				// RETORNA REFERENCIA REAL AL OBJETO
				return &(table[index]->getValueRef());
			}
			index = (original + step) % TABLE_SIZE;
			step++;
		}
		return nullptr;
	}

	bool actualizar(string key, const T& nuevoValor) {
		int index = hashFunction(key);
		int original = index, step = 1;

		while (table[index] != nullptr) {
			if (table[index] != TOMBSTONE &&
				table[index]->getKey() == key) {

				table[index]->setValue(nuevoValor); // SOBREESCRIBIR OBJETO
				return true;
			}
			index = (original + step) % TABLE_SIZE;
			step++;
		}
		return false;
	}




};

template<typename T>
HashEntidad<T>* HashTable<T>::TOMBSTONE = (HashEntidad<T>*) - 1;

