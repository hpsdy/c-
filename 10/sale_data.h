#ifndef SALE_DATA
#define SALE_DATA
#include"head.h"
class sale_data{
	public:
	sale_data()=default;
	friend istream & operator>>(istream &,sale_data &);
	bool operator<(const sale_data & sale){
		return No<sale.getNo();
	}
	sale_data & operator+(const sale_data &sale){
		if(No==sale.getNo()){
			count += sale.getCount();
			all_price += sale.getAllPrice();
		}else{
			*this = sale;
		}
		return *this;
	}	
	string getNo()const{
		return No;
	}
	int getCount()const{
		return count;
	}
	double getAllPrice()const{
		return all_price;
	}


	private:
	string No;
	int count=0;
	double all_price=0.0;
};
istream & operator>>(istream &in,sale_data &sale){
	in>>sale.No>>sale.count>>sale.all_price;
	return in;
}
#endif
