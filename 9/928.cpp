#include"head.h"
typedef forward_list<string> fs;
fs & ainsert(fs &str,const string &str1,const string &str2){
	bool is=0;
	auto b = str.begin();
	auto pre = str.before_begin();
	for(;b!=str.end();){
		cout<<"init:"<<*b<<endl;
		if(*b==str1){
			b = str.insert_after(b,str2);
			is=1;
		}else{
			++b;	
		}
		++pre;
	}
	if(!is){
		str.insert_after(pre,str2);	
	}
	return str;
}


int main(){
	//deque<int> a{1,2,3};
	string a="abc";
	auto b = a.begin();
	cout<<*b<<endl;
	a.push_back('a');
	cout<<*b<<endl;
	cout<<a<<endl;
	return 0;
	fs arr = {"abc","cba"};
//	fs test = ainsert(arr,"abc","qinhan");	
	fs test = ainsert(arr,"qin","han");	
	for(auto &c: test){
		cout<<c<<endl;
	}
/*	cout<<"==========="<<endl;
	for(auto &c: test2){
		cout<<c<<endl;
	}*/
	return 0;

}
