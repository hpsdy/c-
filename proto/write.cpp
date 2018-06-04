//#include"world.pb.h"
#include"world_bak.pb.h"
#include<iostream>
#include<fstream>
using namespace std;
using namespace world;
int main(){
	hello_w he;
	ofstream out("./log",ios::out);
	he.set_id(100);
	he.set_str("qinhan");
	//he.set_opt(666);
	hello_w_ctype *p = he.mutable_oc();
	p->set_id(110119);
	p->set_desc("你好呀，我的朋友");
	he.add_some("bai");
	he.add_some("du");
	int size = he.some_size();
	cout<<size<<endl;
	for(int i=0;i<size;++i){
		cout<<he.some(i)<<endl;
	}		
	if(!he.SerializeToOstream(&out)){
		cerr<<"serialize fail"<<endl;
		return 0;
	}

	return 0;

}
