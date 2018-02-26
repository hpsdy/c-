#include<iostream>
#include<string>
using namespace std;
int main(){
	string in;
	cout<<"begin:"<<endl;
	while (getline(cin,in)){
		cout<<in.size()<<" : "<<in<<endl;
	}
	return 0;
}
