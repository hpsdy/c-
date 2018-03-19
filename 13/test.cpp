#include <iostream>
using namespace std;
class test{
	public:
		test(){
			cout<<"test const"<<endl;
		}
		test(int n){
			cout<<"test:"<<n<<endl;
		}

		~test(){
			cout<<"test destroy"<<endl;
		}

};
int main(){
	cout<<"begin:"<<endl;
	test a();
	test b();
	test c;
	test d(10);
	test *e = new test;
	test *f = new test();
	test *j = new test(99);
//	a();
//	b();
	return 0;
}
