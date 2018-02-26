#include"head.h"
int main(){
	echo: int num=100;

	cout<<"num:"<<num<<endl;
	num=99;
	cout<<"num:"<<num<<endl;
	goto echo;
	cout<<"num:"<<num<<endl;
	return 0;
}
