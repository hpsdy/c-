#include<iostream>
#include"line.h"
#include"other.cpp"
#include<gflags/gflags.h>
using namespace std;
DEFINE_string(name,"hello","some string");
int main(int argc,char **argv){
	gflags::ParseCommandLineFlags(&argc,&argv,true);
	cout<<FLAGS_name<<endl;
	print();
	return 0;
}
