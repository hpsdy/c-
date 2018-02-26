#include"head.h"
#include<stdexcept>
typedef vector<int>::iterator ite;
ite & find(ite & begin,ite & end,int num){
	while(begin!=end){
		if(*begin==num){
			return begin;
		}
		++begin;
	}
	throw runtime_error("no find");
}
int main(){
	vector<int> arr{1,2,3,4,5,6,7,8,9};
	auto begin = arr.begin();
	auto end = arr.end();
	int num = 11;
	try{
		auto nite = find(begin,end,num);
		cout<<*nite<<endl;
	}catch(runtime_error e){
		cout<<e.what()<<endl;
	}	
	return 0;
}
