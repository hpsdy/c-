#include<iostream>
#include<map>
//#include "sales_data.h"
using namespace std;
#include "sales_data.h"
const int two = 333;
int three = 999;
string four = "qinhan";
extern int w;
int main(){
	
	cout<<two<<" "<<three<<" "<<four<<" "<<w<<endl;
	cout<<one<<endl;
	map<int,sales_data> s_map;
	cout<<"input<'no,num,unit_price'>:"<<endl;
	for(int i=1;i<=2;i++){		
		s_map[i].print_info();
		cin>>s_map[i].bNo>>s_map[i].saleNum>>s_map[i].price;
	}
	cout<<"sale_1:"<<s_map[1].bNo<<endl;
	cout<<"sale_2:"<<s_map[2].bNo<<endl;
	if (s_map[1].bNo==s_map[2].bNo){
		cout<<"bNo:"<<s_map[1].bNo<<endl;
		cout<<"cout:"<<s_map[1].saleNum+s_map[2].saleNum<<endl;
		cout<<"per:"<<(s_map[1].saleNum*s_map[1].price+s_map[2].saleNum*s_map[2].price)/(s_map[1].saleNum+s_map[2].saleNum)<<endl;
	}else{
		cout<<"bNo error"<<endl;
	}
	return 0;
}
