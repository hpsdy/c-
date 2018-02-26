#include"head.h"
class someType{
	public:
	typedef string::size_type pos;
	typedef int arr[3];
	pos test();
};
int main(){
	someType::pos a=10;
	someType::arr b = {1,2,3};
	cout<<a<<endl;
	cout<<b<<endl;
	someType c;
	c.test();
	return 0;
}
