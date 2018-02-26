#include"head.h"
#include<sstream>
int main(){
	string x;
	int n=0;
	while(cin>>x){
		++n;
		cout<<n<<":"<<x<<endl;
	}
	stringstream str("abcde");
	string str_c = str.str();
	cout<<str_c<<endl;
	str_c = str.str();
	cout<<str_c<<endl;
	str.str("edcba");
	str_c = str.str();
	cout<<str_c<<endl;
	return 0;
}
