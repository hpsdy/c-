#include"head.h"
string xchange(string str,const string &os,const string &ns){
	auto p=0;
	while((p=str.find(os,p))!=string::npos){
		str.replace(p,os.size(),ns);
		p+=ns.size();
		cout<<"p:"<<str[p]<<endl;
	}
	return str;
}
int main(){
	string str1,str2,str3,str4;
	getline(cin,str1);
	getline(cin,str2);
	getline(cin,str3);
	cout<<str1<<'\t'<<str2<<'\t'<<str3<<endl;
	str4 = xchange(str1,str2,str3);
	cout<<str4<<endl;
	return 0;
}
