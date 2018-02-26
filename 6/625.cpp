#include<iostream>
#include<typeinfo>
using namespace std;

int main(int argc,char * argv[]){
	string str="";
	while(true){
		if(*argv!=0){
			auto tmp = *argv++;
			cout<<"type:"<<typeid(tmp).name()<<endl;
			str += tmp;
			cout<<tmp<<endl;
		}else{
			break;
		}
	}
	cout<<str<<endl;
	cout<<argc<<endl;
	return 0;
}
