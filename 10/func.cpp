#include"head.h"
void print(){
	cout<<"print"<<endl;
}
void (*test())(){
	return print;
}
int main(){
	void (*p)()  = test();
	p();
	return 0;
}
