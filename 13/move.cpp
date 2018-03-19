#include<iostream>
#include<string>
using namespace std;
int main(){
	string a = "100";
	string &&b = std::move(a);
	cout<<a<<endl;
	string c = b;
	b="99";
	cout<<a<<endl;
	cout<<"b:"<<b<<endl;
	cout<<"c:"<<c<<endl;
	string d = std::move(a);
	cout<<a<<endl;
	cout<<"d:"<<d<<endl;
	return EXIT_SUCCESS;
}
