#include"text.h"
#include<fstream>
#include<iostream>
#include<string>
#include<cctype>
using namespace std;
void clearup_str(string &line){
	string str = "";
	for(auto b = line.begin(),e = line.end();b != e; ++b){
		if(!ispunct(*b)){
			str += tolower(*b);
		}
	}
	line = str;
}
text::text(ifstream &fn):file(new vector<string>()){
	string fline;
	size_t size=0;
	while(getline(fn,fline)){
		++size;
		clearup_str(fline);
//		cout<<fline<<endl;
		file->push_back(fline);
		stringstream ss(fline);
		string key;
		while(ss>>key){
			auto &tmp = keymap[key];
			if(!tmp){
				tmp.reset(new set<line>);
			}	
			auto ret=tmp->insert(size);
		}		
	}

}
result text::query(string str){
/*	for(const auto &c:keymap){
		cout<<c.first<<'\t';
		for(const auto &ic:*(c.second)){
			cout<<ic<<'\t';
		}
	}*/
	cout<<endl;
	clearup_str(str);
	static shared_ptr<set<line>> emp(new set<line>());
	auto end = keymap.end();
	auto ret = keymap.find(str);
	if(ret!=end){
		return {str,ret->second,file};
	}else{
		return {str,emp,file};
	}
} 
string make_plural(int size,string prefix,string str){
	return (size>1)?(prefix+str):prefix;
}
void print(ostream &out,result &ret){
	out<<"search:"<<ret.key<<endl;
	out<<"count:"<<ret.lines->size()<<make_plural(ret.lines->size(),"time","s")<<endl;
//	out<<"count:"<<ret.lines->size()<<endl;
	for(const auto &c:*(ret.lines)){
		out<<"(line:"<<c<<");line:"<<(*(ret.file))[c-1]<<endl;
//		out<<c<<endl;
	}			
}
