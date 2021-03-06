#pragma once

#include <memory>
#include <iostream>

using namespace std;

template<class T> class Vector {
	unique_ptr<T[]> m_array;

	size_t m_capacity; //die L�nge des Arrays m_array
	size_t m_size; //die Anzahl Elemente im Array m_array

public:
	Vector(size_t capacity = 10)
		: m_array(new T[capacity]), m_capacity(capacity), m_size(0) {};

	Vector(const Vector& v)
		: m_array(new T[v.m_capacity]), m_capacity(v.m_capacity), m_size(v.m_size) {
		for (size_t i = 0; i < m_size; i++) {
			m_array[i] = v[i];
		}
	}
	Vector(Vector&& v) : m_array(move(v.m_array)), m_capacity(v.m_capacity), m_size(v.m_size) {
		v.m_size = v.m_capacity = 0;
	}

	bool isEmpty() const { return m_size = 0; };

	Vector(size_t size, const T& val)
		: m_array(new T[size]), m_capacity(size), m_size(size) {
		for (size_t i = 0; i < m_size; i++) m_array[i] = val;
	}

	Vector& operator=(const Vector& v) {
		if (this != &v) {
			m_array.reset(new T[v.m_capacity]);
			m_capacity = v.m_capacity;
			m_size = v.m_size;
			for (size_t i = 0; i < m_size; i++) m_array[i] = v[i];
		}
		return *this;
	}

	Vector& operator=(Vector&& v) {
		if (this != &v) {
			m_array.release();
			m_array.swap(v.m_array);
			m_capacity = v.m_capacity;
			m_size = v.m_size;
			v.m_capacity = v.m_size = 0;
		}
		return *this;
	}

	//index Operator mit nur Lesezugriff - T als reference im R�ckgabetyp da man nicht weiss was das f�r ein Typ sein wird. 
	const T& operator[](size_t i) const {
		if (i >= m_size) throw out_of_range("index is too large");
		return m_array[i];
	}

	T& operator[](size_t i) {
		if (i >= m_size) throw out_of_range("index is too large");
		return m_array[i];
	}

	
	
	 void push_back(const T& data) {
		 if (m_size == m_capacity) increaseCapacity();
		 m_array[m_size++] = data;
	 }

	 // verwendung von Rechtsreferenten. 
	 template<typename... Args> 
	 T& emplace_back(Args&&... args) {
		 if (m_size >= m_capacity) increaseCapacity();
		 return m_array[m_size++] = T(forward<Args>(args)...);
	 }

	friend ostream& operator<<(ostream& os, const Vector& v) {
		os << '[';
		if (v.m_size > 0) os << v[0];
		for (size_t i = 1; i < v.m_size; i++) {
			os << ',' << v[i];
		}

		return os << ']';
	}

private:
	void increaseCapacity() {
		size_t capacity = 1 + 3 * m_capacity / 2;
		unique_ptr<T[]> array(new T[capacity]);
		for (size_t i = 0; i < m_size; i++) {
			array[i] = m_array[i];
		}
		m_array = move(array);
	}
	
};
