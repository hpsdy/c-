#include"head.h"
int main(){
	string str="abcdqinhan";
	auto s = str.erase(0,4);
	cout<<str<<endl;
	cout<<s<<endl;
	map<string,size_t> maps;
	vector<string> strs;
	myread("string.txt",strs,string(""));
	unordered_set<string> sets;
	for(auto &c:strs){
		lower(c);
		sets.insert(c);
		pair<map<string,size_t>::iterator,bool> tmp = maps.insert({c,1});
		if(!tmp.second){
			++tmp.first->second;
		}
	}
	for(auto &c:maps){
		cout<<c.first<<":"<<c.second<<endl;
	}
	cout<<"========="<<endl;
	for(auto &c:sets){
		cout<<c<<endl;
	}
	return 0;
}
