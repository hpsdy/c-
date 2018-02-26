#include"head.h"
class test{
	public:
	static const int num=100;
	int sm = 99;
};
int main(){
	cout<<test::num<<endl;
	cout<<test::sm<<endl;
	return 0;
}
