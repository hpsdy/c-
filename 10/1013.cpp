#include"head.h"
#include<functional>
using namespace std::placeholders;
bool lt5(const string &str,size_t size){
	return str.size()>=size;
}
int main(){
	fstream fn("string.txt",fstream::in);
	if(fn){
		vector<string> strs;
		string str;
		while(fn>>str){
			cout<<str<<'\t';
			strs.push_back(str);
		}	
		cout<<"===================="<<endl;
		fn.close();
		auto e = partition(strs.begin(),strs.end(),bind(lt5,_1,5));
		auto b = strs.begin();
		while(b!=e){
			cout<<*b<<'\t';
			++b;
		}
		cout<<endl;
	}
	return 0;
}
