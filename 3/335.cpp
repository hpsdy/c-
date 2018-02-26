#include<iostream>
#include<string>
//#include<cstddef>
using namespace std;
int main(){
	string init[] = {"10","20","30","40"};
	auto *ps = begin(init);
	auto *pe = end(init);
	cout<<"diff:"<<pe-ps<<endl;
	cout<<"size:"<<sizeof(init)<<endl;
	while(ps<=pe){
		*ps = "hwo";
		++ps;
	}	
	for(auto c:init){
		cout<<c<<endl;
	}
	return 0;
}
