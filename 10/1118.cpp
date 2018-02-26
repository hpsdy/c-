#include"head.h"
#include<utility>
int main(){
	map<string,string> maps = {{"qin","han"},{"han","qin"},{"china","hongku"}};
	pair<string,string>::const_iterator b = maps.cbegin();
	pair<string,string>::const_iterator e = maps.cend();
	while(b!=e){
		cout<<b->first<<":"<<b->second<<endl;
		++b;
	}	
	set<string> sets = {"abc","cba"};
	set<string>::iterator sb = sets.begin();
	set<string>::iterator se = sets.end();
	while(sb!=se){
		cout<<*sb<<endl;
		++sb;
	}
	return 0;

}
