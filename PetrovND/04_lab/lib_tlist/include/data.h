#ifndef _DATA_H
#define _DATA_H

class Data {
public:
	//virtual Data* copy() const = 0;
	virtual bool operator <(const Data& data)const = 0;
	virtual bool operator <=(const Data& data)const = 0;
	virtual bool operator >(const Data& data)const = 0;
	virtual bool operator >=(const Data& data)const = 0;
	virtual bool operator ==(const Data& data)const = 0;
	virtual bool operator !=(const Data& data)const = 0;
};

#endif 