#include"head.h"
#include<iterator>

int main(){
	vector<string> vt;
	myread<vector<string>>("string.txt",vt,string(""));
	ifstream in("string.txt");
	istream_iterator<string> fn(cin);
	auto fn_cp = fn;
	cout<<"0:"<<*fn_cp<<endl;
	cout<<"============="<<endl;
	cout<<"1:"<<*++fn_cp<<endl;
	cout<<"============="<<endl;
	cout<<"2:"<<*++fn_cp<<endl;
	cout<<"============="<<endl;
	cout<<"3:"<<*++fn_cp<<endl;
	cout<<"============="<<endl;
	cout<<"4:"<<*fn<<endl;
	cout<<"step_1"<<endl;
	istream_iterator<string> ep;
	cout<<"step_2"<<endl;
	int i=0;
	while(fn!=ep){
		++i;
		cout<<i<<":";
		cout<<*fn++<<'\t';
	}
	cout<<endl;
	cout<<"============"<<endl;
	vector<string> nt(fn_cp,ep);
	print(vt);
	cout<<"============="<<endl;
	print(nt);
	cout<<"============="<<endl;
	cout<<*++fn_cp<<endl;
	cout<<*++fn<<endl;
	cout<<*++fn<<endl;
	cout<<*++fn<<endl;
	cout<<"============="<<endl;
	cout<<*++fn_cp<<endl;
	cout<<"============="<<endl;
	cout<<*++fn_cp<<endl;
	cout<<"============="<<endl;
	cout<<*++fn_cp<<endl;
	return 0;
}
