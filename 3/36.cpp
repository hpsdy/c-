#include<iostream>
#include<string>
using namespace std;
int main(){
	string in;
	getline(cin,in);
	cout<<in.size()<<endl;
	for(char &c:in){
		c = 'X';
	}
	cout<<in<<endl;
	return 0;
}
