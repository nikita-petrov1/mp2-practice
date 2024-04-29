#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <vector>
#include "headRingList.h"
#include "monom.h"


class  TPolynom {
private:
	string name;
	THeadRingList<Monom> monomes;

	vector<string> splitIntoMonoms(const string& polynom) const;
	void parse(const vector<string>& stringMonoms); 
	void rename();
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const TPolynom& p);
	TPolynom(const THeadRingList<Monom>& rList);
	string getName() const { return name; }
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;
	TPolynom operator+(const TPolynom& p);
	TPolynom operator-(const TPolynom& p);
	TPolynom operator*(const TPolynom& p);
	bool operator==(const TPolynom& p) const;
	double operator()(double x, double y, double z);
	const TPolynom& operator=(const TPolynom& p);
	friend ostream& operator<<(ostream& os, const TPolynom& polynom);
};
#endif 