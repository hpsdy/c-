#include"head.h"
size_t count(){
	static size_t num=0;
	return ++num;
}
int main(){
	cout<<count()<<endl;	
	cout<<count()<<endl;	
	return 0;
}
