#include"head.h"
int main(){
	int a = 10;
	int e = 99;
	float b = static_cast<float>(a);
	cout<<typeid(a).name()<<endl;
	cout<<typeid(b).name()<<endl;
	int c = (++a,++e);
	cout<<c<<endl;
	cout<<a<<endl;
	return 0;
}
