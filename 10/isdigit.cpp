#include"head.h"
int main(){
	int a=10;
	string str = "123a";
	for(auto &c:str){
		cout<<c<<":"<<isdigit(c)<<endl;
	}
//	cout<<isdigit(a)<<endl;
	return 0;

}
