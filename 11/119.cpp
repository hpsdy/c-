#include"head.h"
int main(){
	ifstream fs("string.txt");
	if(fs){
		map<string,set<int>> info;
		string line;
		string word;
		int lineno=0;
		while(getline(fs,line)){
			++lineno;
			cout<<"lineno:"<<lineno<<">>"<<line<<endl;
			istringstream ss(line);
			while(ss>>word){
				lower(word);
				info[word].insert(lineno);
			}
		}
		for(auto &c:info){
			cout<<c.first<<":";
			for(auto &ic:c.second){
				cout<<ic<<'\t';
			}
			cout<<endl;
		}
		
	}

	return 0;
}
