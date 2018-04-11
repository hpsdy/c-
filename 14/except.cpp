#include<iostream>
#include<exception>
#include<stdexcept>
using namespace std;
int main(){
	try{

		throw 100;
		throw out_of_range("xxxyyy");
	}catch(int E){
		cout<<"~~~"<<endl;
		cout<<E<<endl;
		cout<<"~~~"<<endl;
	}catch(logic_error E){
		cout<<"+++"<<endl;
		cout<<E.what()<<endl;
		cout<<"+++"<<endl;
	}
	cout<<"==="<<endl;
	return 0;
}
