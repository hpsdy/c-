#include"head.h"
string  xchange(string str,const string &nstr,const string &ostr){
	auto b = str.begin();
	auto e = str.end();
	auto ib = ostr.begin();
	auto ie = ostr.end();
	typedef decltype(b) type;
	auto len = ostr.size();
	typedef decltype(len) size;
	type sbegin,send;
	size num=1;
	bool is=0;
	for(;b!=e;++b){
		if(*b==*ib){
			if(num==1){
				sbegin=b;
			}
			if(num==len){
				send = b;
				is=1;
				break;
			}
			if(num<len){
				++num;
				++ib;
			}
		}else{
			if(num>1 && num<=len){
				num=1;
				ib=ostr.begin();
			}
		}
		
	}
	if(is){
		cout<<*sbegin<<'\t'<<*send<<endl;
		send = send+1;
		auto ite1 = str.erase(sbegin,send);
		str.insert(ite1,nstr.begin(),nstr.end());
	}
	return str;
}
int main(){
	string a="hello world";
	string b="秦瀚";
	string c="d";
	string e=xchange(a,b,c);
	cout<<e<<endl;
	return 0;


}
