#include"head.h"
#include<iterator>
int main(){
	string xstr = "abcdef";
	auto x = xstr.erase(xstr.begin(),xstr.begin()+1);
	cout<<*x<<endl;


	return 0;
	char arr[] = "abc";
	char arr1[] = {'a','b','c','\0'};
	cout<<sizeof(arr)/sizeof(*arr)<<endl;
	cout<<sizeof(arr1)/sizeof(*arr1)<<endl;
	cout<<strlen(arr)<<endl;
	vector<int> a;
	//fill_n(a.begin(),10,10);
	auto ite = back_inserter(a);
	*ite=99;
	*ite=100;
	fill_n(back_inserter(a),10,10);
	//fill_n(ite,10,10);
	for(auto &c:a){
		cout<<c<<endl;
	}
	return 0;

}
