#ifndef PERSON
#define PERSON
#include"head.h"
struct person{
	string name;
	string addr;
	string getname() const{
		return name;
	}
	string getaddr() const;
};
string person::getaddr() const{
	return addr;
}
#endif
