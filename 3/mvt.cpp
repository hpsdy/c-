#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>
using namespace std;
int main(){
	vector<int> a = {1,2,3};
	vector<int> b = {1,2,3};
	vector<int> c(3,10);
	if(b==a){
		cout<<"=="<<endl;
	}
	cout<<c[2]<<endl;
	cout<<c.empty()<<endl;
	cout<<typeid(c.begin()).name()<<endl;
	cout<<typeid(c).name()<<endl;
	return 0;
}
