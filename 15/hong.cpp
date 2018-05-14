#include <iostream>
using namespace std;
void test(){
#define xxx "xyz"
	cout<<"inline1:"<<xxx<<endl;
	cout<<"inline2:"<<__PRETTY_FUNCTION__<<endl;
}
int main(){
	test();
	cout<<"out:"<<xxx<<endl;
	for(int i=0;i<10;++i){
		cout<<i<<endl;
		throw;
	}
	return 0;
}
