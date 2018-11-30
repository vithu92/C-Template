#include "Vector.h"
#include <vector>
#include <set>

class C {
	int m_x;
public:
	C(int x = 0) : m_x(x) {}
	friend ostream& operator<<(ostream& os, const C& c) {
		return os << c.m_x;
	}
};

template<class T>
class D {
	T m_x;

public:
	D( T x = 0): m_x(x){}
	friend ostream& operator<<(ostream& os, const D& d) {
		return os << d.m_x;
	}
};

/*template<template<typename, typename> class Con, class T, class A>
ostream& operator<<(ostream& os, const Con<T,A>& c) {
	os << "generisch[";
	auto& it = c.begin();
	if (it != c.end()) os << *it++;
	while(it != c.end()) {
		os << ',' << *it++;
	}	
	return os << ']';
}*/

template<template<typename...> class Con, class... Rest>
ostream& operator<<(ostream& os, const Con<Rest...>& c) {
	os << "generisch[";
	auto it = c.begin();
	if (it != c.end()) os << *it++;
	while (it != c.end()) {
		os << ',' << *it++;
	}
	return os << ']';
}
int main() {
	Vector<double> v1(5, 1.9);

	cout << v1 << endl;
	v1[0] = 33;
	cout << v1 << endl;
	v1[2] = 33;
	cout << v1 << endl;
	Vector<double> v11;
	v11 = v1;
	cout << "nach Zuweisung: " << v11 << endl;
	Vector<double> v12;
	v12 = move(v11);
	cout << "nach Verschiebung: " << v12 << endl;
	cout << "verschobener Vektor: " << v11 << endl;

	auto v13(v1);
	cout << "nach copy-ctor: " << v13 << endl;

	auto v14(move(13));
	cout << "nach move-ctor: " << v14 << endl;
	cout << "verschobener Vektor: " << v13 << endl;

	Vector<C> v2(4, 100);
	cout << v2 << endl;
	v2.push_back(200);
	v2.push_back(C(300));
	cout << v2 << endl;


	//Vector<C> v2(4, 100);
	//cout << v2 << endl;

	Vector<Vector<double>> vv(3, v1);
	cout << vv << endl;
	vv.emplace_back(2, 99.99);
	cout << vv << endl;

	cout << D<int>(4) << endl;

	set<double> s1 = { 1.1, 2.2, 3.3 };
	cout << s1 << endl;

}