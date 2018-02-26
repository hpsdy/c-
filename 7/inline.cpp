#include"head.h"
class test1{
	friend class test;
};

class test{
	friend class test1;
	friend void print(test &);;
	private:
	int num=100;
};
//void print(test &);
void print(test &t){
	cout<<t.num<<endl;
}
int main(){
	test t;
	print(t);
	return 0;
}

