#include<iostream>
#include<string>
using namespace std;
int main(){
	string a,b;
	cin>>a>>b;
	if(a==b){
		cout<<"a,b相等"<<endl;
	}else if(a>b){
		cout<<"max:"<<a<<endl;
	}else{
		cout<<"max:"<<b<<endl;
	}
	std::string::size_type a_size = a.size();
	size_t b_size = b.size();
	if(a_size==b_size){
		cout<<"a,b长度相等"<<endl;
	}else if(a_size>b_size){
		cout<<"max_len:"<<a<<endl;
	}else{
		cout<<"max_len:"<<b<<endl;
	}
	return 0;
}
