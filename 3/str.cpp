#include<iostream>
#include<string>
using namespace std;
int main(){
	string in;
	getline(cin,in);
	cout<<in.size()<<endl;
	for(auto &c:in){
		cout<<c<<endl;
		if(isalpha(c)){
			auto tmp = toupper(c);
			cout<<"max:"<<tmp<<endl;
			c = tmp;
		}
	}
	cout<<in<<endl;
	return 0;
}
