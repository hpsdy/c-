#include<iostream>
#include<string>
#define ONE "abcdef"
using namespace std;
int main(){
	::std::string aaa="aaa";
	string str;
	string ty = "qh";
	str = ONE":"+ty;
	cout<<str<<endl;
	cout<<aaa<<endl;
	int nm=999;
	string strnum = (string)(nm);
	cout<<strnum<<endl;
	return 0;
}
