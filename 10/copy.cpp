#include"head.h"
int main(){
	string str = "abcdef";
	string cp = "1";
	auto e = cp.back();
	cout<<e<<endl;
//	auto p = copy(str.begin(),str.end(),cp.end()-6);
	auto p = copy(str.begin(),str.end(),cp.begin());
	cout<<*(p-7)<<endl;
	cout<<cp<<endl;
	return 0;


}
