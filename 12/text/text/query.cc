#include<iostream>
#include<memory>
#include<fstream>
#include<cctype>
#include<string>
#include<cstdlib> //for EXIT_FAILURE
#include"text.h"
using namespace std;
ifstream & run(ifstream &fn){
	text q(fn);
	while(true){
		cout<<"请输入要查询的单词或者输入q离开:"<<endl;
		string str;
		if(!(cin>>str) || str=="q"){
			cout<<"end"<<endl;
			break;
		}
		auto ret = q.query(str);
		print(cout,ret);
	}
	return fn;
}
int main(int argc,char **argv){
	ifstream fn;
	cout<<argc<<endl;
	cout<<argv[1]<<endl;
	//return 0;
	if(argc<2 || !(fn.open(argv[1]),fn)){
		cout<<"input file error"<<endl;
		return EXIT_FAILURE;
	}
	run(fn);		
	return 0; 
}
