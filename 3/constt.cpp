#include<iostream>
using namespace std;
int main(){
	const int a=100;
	cout<<&a<<endl;
	int b = 10;
	cout<<(b=a)<<b<<endl;
	return 0;
}
