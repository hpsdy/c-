#include"head.h"
#include"sale_data.h"
int main(){
	vector<sale_data> sales;
	sale_data sale;
	while(cin>>sale){
		sales.push_back(sale);
	}
	sort(sales.begin(),sales.end());
	for(auto &c:sales){
		cout<<c.getNo()<<":"<<c.getCount()<<";all:"<<c.getAllPrice()<<endl;
	}
	cout<<"=================="<<endl;
 	auto sale_ite = sales.begin();
	auto No = sale_ite->getNo();
	auto e = find_if(sales.begin(),sales.end(),[No](const sale_data &sale){return No!=sale.getNo();});
	sale_data init;
	auto sum = accumulate(sales.begin(),e,init);		
	cout<<sum.getNo()<<":"<<sum.getCount()<<";all:"<<sum.getAllPrice()<<endl;
	return 0;
}
