#include"head.h"
int main(){
	map<string,int> maps;
	ifstream fn("string.txt");
	string word;
	while(fn>>word){
		++maps[word];
	}
	decltype(maps)::iterator fd = maps.find("qinhan");
	pair<string,int> x = *fd;
	cout<<(*fd).first<<":"<<fd->second<<endl;
	return 0;
}
