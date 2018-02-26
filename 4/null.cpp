#include "head.h"
int main(){
	char b = ' ';
	char c = '\0';
	string a = "\0";
	int *p = nullptr;
	if(b){
		cout<<'b'<<endl;
	}

	if(c){
		cout<<'c'<<endl;
	}
	if(p){
		cout<<"*p"<<endl;
	}
	cout<<"a:"<<a<<endl;;
	if(10>2+10){
		cout<<">"<<endl;
	}else{
		cout<<(10>2+5)<<endl;
	}
	return 0;
}
