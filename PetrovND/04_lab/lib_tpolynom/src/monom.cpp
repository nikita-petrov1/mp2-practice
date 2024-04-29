#include "monom.h"
#include <sstream>

Monom::Monom() : coeff(0.0), degree(-1) {};

Monom::Monom(double _coeff,  int _degree){
	if (_degree < -1 || _degree > 999){
		throw ("Degree must be from -1 to 999");
	}
	coeff = _coeff;
	degree = _degree;
}

bool Monom::operator<(const Data& data)const {
	const Monom& monom = static_cast<const Monom&>(data);
	return degree < monom.degree;
}

Monom Monom::operator+(const Data& data) {
	const Monom& monom = static_cast<const Monom&>(data);
	return Monom(coeff + monom.coeff, degree);
}

bool Monom::operator<=(const Data& data)const {
	const Monom& monom = static_cast<const Monom&>(data);
	return degree <= monom.degree;
}

bool Monom::operator>(const Data& data)const {
	const Monom& monom = static_cast<const Monom&>(data);
	return degree > monom.degree;
}

bool Monom::operator>=(const Data& data)const {
	const Monom& monom = static_cast<const Monom&>(data);
	return degree >= monom.degree;
}

bool Monom::operator==(const Data& data)const {
	const Monom& monom = static_cast<const Monom&>(data);
	return coeff == monom.coeff && degree == monom.degree;
}

bool Monom::operator!=(const Data& data)const {
	const Monom& monom = static_cast<const Monom&>(data);
	return coeff != monom.coeff || degree != monom.degree;
}

ostream& operator<<(ostream& os, const Monom& m) {
	os << m.toStr();
	return os;
}

string Monom::toStr() const {
	stringstream ss;
	string res = "";
	if (coeff >= 0) { ss << "+" << coeff; }
	else { ss << coeff; }
	int e, d, s;
	e = degree % 10;
	d = degree / 10 % 10;
	s = degree / 100;
	if (s != 0) { ss << "*x^" << s; }
	if (d != 0) { ss << "*y^" << d; }
	if (e != 0) { ss << "*z^" << e; }
	return ss.str();
}