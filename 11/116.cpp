#include"head.h"
typedef map<string,vector<string>> family;
void add_family(family &f,const string &str){
	f[str];
}
void add_child(family &f,const string &str,const string &child){
	f[str].push_back(child);
}
int main(){
	family fs;
	add_family(fs,"秦");
	add_family(fs,"王");
	add_family(fs,"李");
	add_family(fs,"王");
	add_child(fs,"王","中俄");
	add_child(fs,"王","电话");
	add_child(fs,"王","武汉");
	add_child(fs,"秦","武汉");
	add_child(fs,"李","武汉");
	for(auto &c:fs){
		cout<<c.first<<":";
		for(auto &ic:c.second){
			cout<<ic<<'\t';
		}
		cout<<endl;
	}
	cout<<"================="<<endl;
	typedef  int const at;
	at b=100;
	cout<<b;
	return 0;


}
