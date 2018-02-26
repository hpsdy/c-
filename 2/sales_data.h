#ifndef SALES_DATA_H
#define SALES_DATA_H
#include<string>
extern const int two;
extern int three;
int w = 111222;
struct sales_data{
	std::string bNo;
	int saleNum=0;
	double price=0.0;
	double saleCount=0.0;
	void print_info(){
		cout<<"hello kitty"<<endl;
		cout<<two<<" "<<three<<endl;

	}
};
const int one = 100;
#endif
//std::cout<<two<<endl;
//cout<<three<<endl;
