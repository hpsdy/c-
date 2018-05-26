#include<iostream>
using namespace std;
int main(){
	int a=100;
	int &b = a;
	decltype(b) c = a;
	cout<<c<<endl;
	a=99;
	cout<<c<<endl;
	return 0;

}
