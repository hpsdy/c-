#include <iostream>
using namespace std;
int main(){
	int countVal=0,value=0;
	if(cin>>countVal){
		int cnt = 1;
		while(cin>>value){
			if(value==countVal){
				++cnt;
			}else{
				cout<<"num:"<<countVal<<",size:"<<cnt<<endl;
				countVal=value;
				cnt=1;
			}
		}
		cout<<"num:"<<countVal<<",size:"<<cnt<<endl;
	}
	return 0;
}
