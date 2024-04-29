#include "polynom.h"
#include "parser.h"
#include <string>

TPolynom::TPolynom() : monomes() {
	name = "";
}

TPolynom::TPolynom(const TPolynom& p) : monomes(p.monomes), name(p.name) {}

TPolynom::TPolynom(const THeadRingList<Monom>& rList) {
	for (auto& m : rList) {
		monomes.descendingInsert(m);
	}
	if (monomes.isEmpty()) { monomes.insertFirst(Monom(0, 0)); }
	rename();
}

void TPolynom::rename() {
	name.clear();
	for (auto& m : monomes) {
		name += m.toStr();
	}
	if (name[0] == '+') { name.erase(0, 1); }
}

vector<string> TPolynom::splitIntoMonoms(const string& polynom) const{
	vector<string> sm;
	string currSM = "";
	for (char c : polynom) {
		if (c != '+' && c != '-') { currSM += c; }
		else {
			sm.push_back(currSM);
			currSM.clear();
			currSM += c;
		}
	}
	sm.push_back(currSM);
	return sm;
}

int extractDegree(const string& monomial) {
	int degree = 0;
	string tmp{ monomial };
	size_t pos[]{ tmp.find('x'),tmp.find('y'),tmp.find('z') };
	const string sep{ "xyz" };
	for (int i = 0; i < 3; i++) {
		if (pos[i] == string::npos) { continue; }
		size_t start = pos[i];
		size_t end = tmp.find_first_of(sep, start + 1);
		if (end == string::npos) { end = tmp.length() + 1; }

		if (end - start == 2) { degree += pow(10, 2 - i) * 1; }
		else if(end- start == 4) { degree += pow(10, 2 - i) * stoi(tmp.substr(start + 2, 1)); }
		else { throw "ERROR: invalid degree!"; }
	}
	return degree;
}

void TPolynom::parse(const vector<string>& stringMonoms) {
	double coeff;
	for (auto& str : stringMonoms) {
		if (str.empty()) { continue; }
		int degree = extractDegree(str);
		size_t end = str.find_first_of("xyz");
		if (end == 1 && str[0] == '-') { coeff = -1; }
		else if (end == 0 || (end == 1 && str[0] == '+')) { coeff = 1; }
		else { coeff = stod(str); }
		Monom m(coeff, degree);
		
		monomes.descendingInsert(m);
	}
	if (monomes.isEmpty()) monomes.insertFirst(Monom(0, 0));
}

TPolynom::TPolynom(const string& _name) {
	string tmp = _name;
	tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end());

	vector<string> parseMonoms = splitIntoMonoms(tmp);
	parse(parseMonoms);
	
	rename();
}

ostream& operator<<(ostream& os, const TPolynom& polynom) {
	os << polynom.name;
	return os;
}
TPolynom TPolynom::dx() const {
	THeadRingList<Monom> rL;
	for (auto& m : monomes) {
		int e, d, s;
		e = m.getDegree() % 10;
		d = m.getDegree() / 10 % 10;
		s = m.getDegree() / 100;
		if (s == 0) { continue; }
		double newCoeff = m.getCoeff() * s;
		int newDegree = (s - 1) * 100 + 10 * d + e;
		rL.insertLast(Monom(newCoeff, newDegree));
	}
	TPolynom pl(rL);
	return pl;
}
TPolynom TPolynom::dy() const {
	THeadRingList<Monom> rL;
	for (auto& m : monomes) {
		int e, d, s;
		e = m.getDegree() % 10;
		d = m.getDegree() / 10 % 10;
		s = m.getDegree() / 100;
		if (d == 0) { continue; }
		double newCoeff = m.getCoeff() * d;
		int newDegree = s * 100 + 10 * (d - 1) + e;
		rL.insertLast(Monom(newCoeff, newDegree));
	}
	TPolynom pl(rL);
	return pl;
}
TPolynom TPolynom::dz() const {
	THeadRingList<Monom> rL;
	for (auto& m : monomes) {
		int e, d, s;
		e = m.getDegree() % 10;
		d = m.getDegree() / 10 % 10;
		s = m.getDegree() / 100;
		if (e == 0) { continue; }
		double newCoeff = m.getCoeff() * e;
		int newDegree = s * 100 + 10 * d + (e-1);
		rL.insertLast(Monom(newCoeff, newDegree));
	}
	TPolynom pl(rL);
	return pl;
}

TPolynom TPolynom::operator+(const TPolynom& p) {
	THeadRingList<Monom> rl(p.monomes);
	for (auto& el : monomes) {
		rl.descendingInsert(el);
	}
	TPolynom pp(rl);
	return pp;
}

TPolynom TPolynom::operator-(const TPolynom& p) {
	THeadRingList<Monom> rl(monomes);
	for (auto& el : p.monomes) {
		rl.descendingInsert(Monom(el.getCoeff() * -1, el.getDegree()));
	}
	TPolynom pp(rl);
	return pp;
}

TPolynom TPolynom::operator*(const TPolynom& p) {
	THeadRingList<Monom> rL;
	for (auto& m1 : monomes) {
		for (auto& m2 : p.monomes) {
			rL.descendingInsert(Monom(m1.getCoeff() * m2.getCoeff(), m1.getDegree() + m2.getDegree()));
		}
	}
	TPolynom pl(rL);
	return pl;
}

double TPolynom::operator()(double x, double y, double z) {
	vector<string> tokens = Parser::splitExpression(name);
	vector<string> res = Parser::infixToPostfix(tokens);
	map<string, double> opVal = Parser::getOperandValues(tokens, x, y, z);
	return Parser::evaluatePostfixExpression(opVal, res);
}

const TPolynom& TPolynom::operator=(const TPolynom& p) {
	if (this == &p) { return *this; }
	monomes.clear();
	for (auto& el : p.monomes) {
		monomes.insertLast(el);
	}
	name = p.name;
}
bool TPolynom::operator==(const TPolynom& p) const {
	return name == p.name;
}