#include<iostream>
#include<string>
using namespace std;
int main(){
	char next = 'y';
	string a,result;
	cout<<"1逐词输入,2整行输入:"<<endl;
	int in=1;
	cin>>in;
	cin.clear();
	cin.ignore();
	cin.sync();
	cout<<"first input:"<<endl;
	if (in==1){
		while(cin>>a){
			if(!result.size()){
				result += a;
			}else{
				result += " " + a;
			}
			cout<<"Y/y继续:"<<endl;
			cin>>next;
			if(next!='y' &&  next!='Y'){
				break;
			}else{
				cout<<"next input:"<<endl;
			}

		}
	}else{
		cout<<"a:"<<a<<endl;
		while (getline(cin,a)){
			cout<<"a:"<<a<<endl;
			if(!result.size()){
				result += a;
			}else{
				result += " " + a;
			}	
			cout<<"Y/y继续:"<<endl;
			cin>>next;
			if(next!='y' &&  next!='Y'){
				break;
			}else{
				cout<<"next input:"<<endl;
			}
			cin.clear();
			cin.ignore();
			cin.sync();

		}
	}
	cout<<"result:"<<result<<endl;
	return 0;
}
