#include<iostream>
#include<string>
#include<memory>
using namespace std;
int main(){
	unique_ptr<int> p(new int(100));
	unique_ptr<int> cp(p.release());

	return 0;
}
