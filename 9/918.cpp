#include"head.h"
list<string> list_w(istream &in){
	string str;
	list<string> arr;
	while(getline(in,str)){
		arr.push_back(str);
	}
	return arr;
}
int main(){
	list<string> arr = list_w(cin);
	typedef list<string>::iterator dite;
	dite b = arr.begin();
	dite e = arr.end();
	for(const dite &i=b;i!=e;++b){
		cout<<*i<<endl;
	}
	int a=10;
	cout<<(a&1)<<endl;
	return 0;

}
