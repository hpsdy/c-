#include<iostream>
#include"line.h"
#include<gflags/gflags.h>
using namespace std;
DEFINE_bool(name,true,"some string");
int main(int argc,char **argv){
	gflags::ParseCommandLineFlags(&argc,&argv,true);
	cout<<FLAGS_name<<endl;
	if(FLAGS_name){
		cout<<"true"<<endl;
	}else{
		cout<<"false"<<endl;
	}
	return 0;
}
