#include<iostream>
#include<fstream>
#include<cstring>

int main(){
	std::fstream fn("log",std::fstream::in|std::fstream::out|std::fstream::ate);
	//std::cout<<"[info]"<<" good:"<<fn.good()<<" bad:"<<fn.bad()<<" end:"<<fn.eof()<<" fail:"<<fn.fail()<<" tellg:"<<fn.tellg()<<" peek:"<<fn.peek()<<std::endl;
	//return 0;
	std::cout<<" tellg:"<<fn.tellg()<<std::endl;
	//fn.seekg(-1,std::ios::cur);
	//fn.seekg(12,std::ios::beg);
	fn.seekg(0,std::ios::beg);
	char x[100] = {'\0'};
	fn.get(x,100,EOF);
	std::cout<<x<<":"<<strlen(x)<<":"<<fn.gcount()<<std::endl;
	std::cout<<"tg:"<<" tellg:"<<fn.tellg()<<" get:"<<fn.get()<<" end:"<<fn.eof()<<std::endl;
	if(fn.good()){
		std::cout<<"[good]"<<" good:"<<fn.good()<<" bad:"<<fn.bad()<<" end:"<<fn.eof()<<" fail:"<<fn.fail()<<std::endl;
		std::cout<<" tellg:"<<fn.tellg()<<std::endl;
		int p = fn.peek();
		std::cout<<" peek:"<<(char)p<<":"<<p<<std::endl;
		std::cout<<fn.good()<<std::endl;
	}else{
		std::cout<<"[bad]"<<" good:"<<fn.good()<<" bad:"<<fn.bad()<<" end:"<<fn.eof()<<" fail:"<<fn.fail()<<std::endl;
		std::cout<<" tellg:"<<fn.tellg()<<std::endl;
		int p = fn.peek();
		std::cout<<" peek:"<<(char)p<<":"<<p<<std::endl;
		std::cout<<fn.good()<<std::endl;
	}		
	fn.seekg(0,std::ios::beg);
	fn.clear();
	std::cout<<"[info]"<<" good:"<<fn.good()<<" bad:"<<fn.bad()<<" end:"<<fn.eof()<<" fail:"<<fn.fail()<<std::endl;
	bool bl;
	//char yy[100] = {'\0'};
	//fn.read(yy,100);
	//std::cout<<"===:"<<yy<<std::endl;
	std::cout<<"================="<<std::endl;
	while (!fn.eof()){
		std::cout<<"========b========="<<std::endl;
		char y[100] = {'\0'};
		fn.getline(y,100);
		std::cout<<fn.tellg()<<":"<<y<<std::endl;
		std::cout<<"========e========="<<std::endl;
	}
	fn.seekg(0,std::ios::beg);
	fn.clear();
	char yy[100] = {'\0'};
	fn.read(yy,100);
	std::cout<<"===:"<<yy<<std::endl;

	fn.close();
	return 0;
}
