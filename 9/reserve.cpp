#include"head.h"
int main(){
	vector<int> a;
	cout<<a.size()<<'\t'<<a.capacity()<<endl;
	a.push_back(10);
	a.push_back(10);
	a.push_back(10);
	cout<<a.size()<<'\t'<<a.capacity()<<endl;
	a.reserve(5);
	cout<<a.size()<<'\t'<<a.capacity()<<endl;
	a.reserve(100);
	cout<<a.size()<<'\t'<<a.capacity()<<endl;
	a.reserve(50);
	cout<<a.size()<<'\t'<<a.capacity()<<endl;
	return 0;
}
