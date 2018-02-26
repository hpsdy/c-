#include<iostream>
using namespace std;

int main(){
	char *r = new char[20];
	char t;
	int l=0;
	while(cin.get(t)){
		if(isspace(t)){
			break;
		}else{
			r[l++] = t;
			if(l==20){
				cout<<"max"<<endl;
				break;
			}
		}
	}	
	r[l] = '\0';
	cout<<r<<endl;
	return 0;
	
}
