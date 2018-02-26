#include"world.pb.h"
#include<iostream>
#include<fstream>
using namespace std;
using namespace world;
int main(){
	ifstream in("./log",ios::in);
	hello_w ie;
	if(!ie.ParseFromIstream(&in)){
		cerr<<"parse fail"<<endl;
		return -1;
	}
	cout<<ie.id()<<endl;
	cout<<ie.str()<<endl;
	cout<<ie.opt()<<endl;
	auto oc = ie.oc();
	cout<<ie.oc().id()<<endl;
	cout<<oc.desc()<<endl;
	int size = ie.some_size();
	cout<<size<<endl;
	for(int i=0;i<size;++i){
		cout<<ie.some(i)<<endl;
	}		
		cout<<ie.some(1)<<endl;
	return 0;

}
