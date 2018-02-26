#include<iostream>
using namespace std;
class a{
	typedef int c;
	public:
		typedef int b[10];

};
int main(){
//	a::c w=100;
	a::b z={0};
//	cout<<w<<endl;
	for(auto &c:z){
		cout<<c<<endl;
	}
	cout<<z<<endl;
	return 0;
}
