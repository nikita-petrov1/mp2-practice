#ifndef _MONOM_H
#define _MONOM_H
#include "data.h"
#include <iostream>
using namespace std;

class Monom : public Data {
private:
	double coeff;
	int degree;
public:
	Monom();
	Monom(double _coeff, int _degree);
	string toStr() const;
	int getDegree() const { return degree; }
	double getCoeff() const { return coeff; }
	bool operator <(const Data& data)const;
	bool operator <=(const Data& data)const;
	bool operator >(const Data& data)const;
	bool operator >=(const Data& data)const;
	bool operator ==(const Data& data)const;
	bool operator !=(const Data& data)const;
	Monom operator +(const Data& data);
	friend ostream& operator<<(ostream& os, const Monom& monom);
};

#endif 