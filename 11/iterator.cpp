#include"head.h"
int main(){
	vector<int> v1 = {1,2,3,4,5,6};
	vector<int> v2 = v1;
	auto b1 = v1.begin();
	auto b2 = b1;
	*b2=100;
	print(v1);
	cout<<"============"<<endl;
	*b1=99;
	print(v1);
	cout<<"============"<<endl;
	cout<<"============"<<endl;
	return 0;

}
