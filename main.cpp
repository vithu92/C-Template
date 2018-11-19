#include "Vector.h"

class C {
	int m_x;
public:
	C(int x = 0) : m_x(x) {}
	friend ostream& operator<<(ostream& os, const C& c) {
		return os << c.m_x;
	}
};

int main() {
	Vector<double> v1(5, 1.9);

	cout << v1 << endl;
	v1[0] = 33;
	cout << v1 << endl;


	Vector<C> v2(4, 100);
	cout << v2 << endl;
	v2.push_back(200);
	v2.push_back(C(300));
	cout << v2 << endl;
	//Vector<C> v2(4, 100);
	//cout << v2 << endl;

	//Vector<Vector<double>> vv(3, v1);
	//cout << vv << endl;


}