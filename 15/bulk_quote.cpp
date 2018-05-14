#include <iostream>
#include <string>
#include "quote.cpp"
using namespace std;
class bulk_quote:public quote{
	public:
	bulk_quote(string name,double pri,int diss,double disc):quote(name,pri),dis_size(diss),discount(disc){}
	bulk_quote* clone() const &{
        	return new bulk_quote(*this);
	}	
	bulk_quote* clone() &&{
        	return new bulk_quote(std::move(*this));
    	}

	virtual double net_price(int size) const;
	private:
	int dis_size;
	double discount;

};
double bulk_quote::net_price(int size) const{
	if(size<=dis_size){
		return price*(1-discount)*size;
	}else{
		return price*(1-discount)*(dis_size)+price*(size-dis_size);
	}
}
