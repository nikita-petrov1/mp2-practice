#include "polynom.h"
#include <iostream>
#include <string>
using namespace std;


int main() {

	string s1, s2;											//5*x^3*y^6-8*y^1*z^2-4*y^2*x^1*z^1-3*y^6*x^3+2*x^3*y^4+8*y^2*z^2-531-8*y^2*z^2
	cout << "Enter first polynom: ";						//5*x^2*z^4*y^3-4*y^3
	cin >> s1;
	cout << endl << "Enter second polynom: ";
	cin >> s2;

	TPolynom p1(s1);
	TPolynom p2(s2);

	cout << "p1: " << p1 << endl << "p2: " << p2 << endl;
	cout << "p1+p2: " << p1 + p2 << endl;
	cout << "p1-p2: " << p1 - p2 << endl;
	cout << "p1*p2: " << p1 * p2 << endl;
	cout << "p1.dx: " << p1.dx() << endl << "p1.dy: " << p1.dy() << endl << "p1.dz: " << p1.dz() << endl;

	cout << "Enter X, Y, Z: " << endl;
	double x, y, z;
	cin >> x >> y >> z;
	cout << "p1(" << x << ", " << y << ", " << z << ") = " << p1(x, y, z);
	
	return 0;
}