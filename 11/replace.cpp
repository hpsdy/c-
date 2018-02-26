#include"head.h"
typedef ifstream ifs;
map<string,string> namemap(ifs &i1);
string myreplace(ifs &i1,ifs &i2){
	auto maps = namemap(i1);
	string str,strs,ret;
	int size=2;
	while(!i2.eof()){
		auto *buf = new char[size];
		i2.read(buf,size);
		cout<<"while:"<<buf<<",size:"<<string(buf).size()<<",end:"<<i2.eof()<<endl;
		cout<<"==========="<<endl;
		strs += buf;
	}
	cout<<"b str:"<<strs<<endl;
	cout<<"++++++++++++++++++"<<endl;
	istringstream is(strs);
	while(is>>str){
		map<string,string>::iterator p;
		if((p=maps.find(str))!=maps.end()){
			ret += p->second;
		}else{
			ret += str;
		}	
		ret += " ";
	}
	return ret;
}
map<string,string> namemap(ifs &i1){
	map<string,string> maps;
	string key,val;
	while(i1>>key && getline(i1,val)){
		if(val.size()>0){
			maps[key] = val;
		}else{
			continue;
		}
	}
	return maps;
}
int main(){
	ifs i1("a.txt");
	ifs i2("b.txt");
	string str =  myreplace(i1,i2);
	cout<<"ret:"<<str<<endl;
	return 0;
}
