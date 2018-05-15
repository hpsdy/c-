#include <iostream>
using namespace std;
__attribute__((constructor)) void p1(){
	cout<<"construct"<<endl;
}
__attribute__((destructor)) void p2(){
	cout<<"destroy"<<endl;
}
class test{
	public:
	test(){
		cout<<"test"<<endl;
	}
};
test a;
int main(){
	cout<<"main"<<endl;
	return 0;
}
