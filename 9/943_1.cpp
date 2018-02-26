#include"head.h"
string xchange(string str,const string &os,const string &ns){
	auto len = os.size();
	if(!len){
		return str;
	}
	auto strlen = str.begin();
	while(b!=str.end()){
		auto ite1 = b;
		auto ite2 = os.begin();
		auto ite2e = os.end();
		while(ite2!=ite2e && *ite1==*ite2){
			++ite1;
			++ite2;
		}
		if(ite2==ite2e){
			auto te = str.erase(b,ite1);
			cout<<"step1"<<endl;
			str.insert(te,ns.begin(),ns.end());	
			cout<<"step2:"<<str<<endl;
			auto tx = str.find(ns);
			b=str.begin()+tx+ns.size();
			cout<<"step3:"<<*b<<endl;
		}else{
			++b;
		}
	}	
	cout<<"step4"<<endl;
	return str;
}
int main(){
	string str1,str2,str3,str4;
	getline(cin,str1);
	getline(cin,str2);
	getline(cin,str3);
	cout<<str1<<'\t'<<str2<<'\t'<<str3<<endl;
	str4 = xchange(str1,str2,str3);
	cout<<"step5"<<endl;
	cout<<str4<<endl;
	return 0;
}
