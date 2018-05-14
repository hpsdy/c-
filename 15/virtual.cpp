#include<iostream>
using namespace std;
class test{
	public:
	virtual void print() const &;
	virtual void print() &{
		cout<<"print"<<endl;
	};
	virtual void print() &&{
		cout<<"&& print"<<endl;
	};


};
void test::print()const &{
	cout<<"const print"<<endl;
}
int main(){
	test one;
	const test two=one; 
	one.print();
	two.print();
	std::move(one).print();
	return 0;

}
