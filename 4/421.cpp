#include "head.h"
int main(){
	int nu = -56;
	string strs = "abcdef";
	cout<<(&strs)<<endl;
	cout<<(&strs[0])<<endl;
	cout<<(sizeof(strs))<<endl;
	cout<<(sizeof(nu))<<endl;
	cout<<(nu)<<endl;
	cout<<(nu<<2)<<endl;
	cout<<(nu>>2)<<endl;
	cout<<(~nu)<<endl;
	int p = 'q';
	cout<<p<<endl;
	cout<<(p<<6)<<endl;
	int q = ~p;
	cout<<q<<endl;
	int w = q<<6;
	cout<<w<<endl;
	return 0;
	vector<int> num;
	int i;
	while(cin>>i){
		num.push_back(i);
	}	
	for (auto &i:num){
		cout<<i<<endl;
		i = (i%2==0)?i:i*2;
	}
	for (auto i:num){
		cout<<i<<endl;
	}
	string str="秦瀚";
	cout<<"str:"<<typeid(str[0]).name()<<endl;
	cout<<"str:"<<str[0]<<endl;
	return 0;
}
