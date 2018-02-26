#include"head.h"

bool comp(const string &s1,const string &s2){
	return s1.size()<s2.size();
}
int main(){
	map<string,int,decltype(comp)*> maps(comp);
	maps["abcasdd"] = 100;
	maps["cedf"] = 100;
	maps["aaaa"] = 99;
	maps["baxds"] = 10;
	maps["aaa"] = 22;
	for(auto &c:maps){
		cout<<c.first<<":"<<c.second<<endl;
	}
	return 0;

}
