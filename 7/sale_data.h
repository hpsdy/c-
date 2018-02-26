#ifndef SALE_DATA
#define SALE_DATA
#include"head.h"
class sale_data;
//istream & read(istream &,sale_data &);
class sale_data{
	friend sale_data add(const sale_data &a,const sale_data &b);
	friend istream & read(istream & is,sale_data & one){
		long double price=0;	
		is>>one.bookNo>>one.soldNum>>price;
		one.money = price*one.soldNum;
		return is;	
	}
	friend ostream & print(ostream & ,const sale_data &);
	public:
	sale_data()=default;
	sale_data(istream & in){
		read(in,*this);
	}
	sale_data(const string No):sale_data(No,0,0){
onMatch
		cout<<"委托构造"<<endl;
	}
	sale_data(const string No,unsigned int sNum,long double uPrice):bookNo(No),soldNum(sNum),money(uPrice*soldNum){
		cout<<"first construct"<<endl;
	}
	void readinfo(istream & is);
//	private:
	//编号
	string bookNo;
	//销量
	unsigned soldNum=0;
	//销售额
	long double money=0;
	public:
	sale_data & combine(const sale_data &);
	string isbn() const {return this->bookNo;}
	long double avg_price() const;
};
sale_data & sale_data::combine(const sale_data & rhs){
	this->soldNum += rhs.soldNum;
	this->money += rhs.money;
	return *this;
}
long double sale_data::avg_price() const {
	return this->money/this->soldNum;
}
sale_data add(const sale_data &,const sale_data&);
//istream & read(istream &,sale_data &);
ostream & print(ostream &,const sale_data &);
sale_data add(const sale_data &a,const sale_data &b){
	sale_data sum=a;
	sum.combine(b);
	return sum;	
}
/*istream & read(istream &is,sale_data &one){
	long double price=0;	
	is>>one.bookNo>>one.soldNum>>price;
	one.money = price*one.soldNum;
	return is;	
}*/
/*sale_data::sale_data(istream & is){
	read(is,*this);
}*/
ostream & print(ostream & out,const sale_data &one){
	out<<"No:"<<one.bookNo<<",num:"<<one.soldNum<<",all_money:"<<one.money<<endl;
	return out;
}
void sale_data::readinfo(istream & is){
	read(is,*this);
}
#endif
