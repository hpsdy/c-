#include"head.h"
#include<utility>
int main(){
	vector<pair<string,int>> vec;
	auto p1 = make_pair("qinhan",100);
	vec.push_back(p1);
	for(auto &c:vec){
		cout<<c.first<<":"<<c.second<<endl;
	}
	return 0;

}
