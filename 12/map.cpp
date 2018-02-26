#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
bool _sort(const string &s1,const string &s2 ){
	return s1.size()<s2.size();
}
int main(){
	if((1,0)){
		cout<<99999<<endl;
	}


	return 0;
	map<string,int> mps={
		{"qinhan",100},
		{"qinh",99},
		{"hellowd",88},
		{"a",10}
	};	
	for(auto &c:mps){
		cout<<c.first<<":"<<c.second<<'\t';
	}
	cout<<endl;
	map<string,int,bool (*)(const string &,const string &)> mp(_sort);
	for(auto &c:mps){
		mp[c.first]=c.second;
	}	
	for(auto &c:mp){
		cout<<c.first<<":"<<c.second<<'\t';
	}
	cout<<endl;
	return 0;	
}
