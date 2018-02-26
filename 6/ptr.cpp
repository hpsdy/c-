#include"head.h"
int a = 100;
char * t(char * p){
	p[1] = 'w';
	return p;
}
string wt(string p){
	p[1] = 'w';
	cout<<"a:"<<a<<endl;
	a=999;
	return p;
}

int main(){
	int *p = 0;
	cout<<sizeof(p)<<endl;
	return 0;
	char str[] = "cba";
	cout<<str<<endl;
	string r = wt(str);
	cout<<str<<endl;
	cout<<r<<endl;
	cout<<"a:"<<a<<endl;
	switch(a){
		case 9999:
			
				int z;
				cout<<"z:"<<z<<endl;
				//break;
			
		case 999:
			z = 898989;
			cout<<1000<<endl;
			cout<<z<<endl;
	}
	return 0;
}
