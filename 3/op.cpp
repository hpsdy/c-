#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main(){
	string a = "qinhan";
	auto s = a.begin();
	auto e = a.end();
	cout<<"ret:"<<(e>s)<<" "<<e-s<<endl;
	return 0;
}
