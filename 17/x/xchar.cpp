#include<iomanip>
#include<iostream>
#include<cstdio>
#include<sstream>
#include<fstream>
#include<cstring>
int main(int argc,char *argv[]){
	std::cout<<argv[0]<<std::endl;
	std::cout<<EOF<<std::endl;
	std::stringstream ss;
	ss<<"abcd";
	char xx[] = "秦瀚";
	int x;
	while((x=ss.get()) != EOF){
		std::cout<<x<<std::endl;
		std::cout<<std::hex<<x<<std::dec<<std::endl;
		//std::cin.unget();
		//std::cin.putback('(');
	}
	std::ifstream fn("log",std::fstream::in);
	fn.seekg(0,std::ios::end);
	std::cout<<"tellg:"<<fn.tellg()<<std::endl;
	int xt;
	if((xt=fn.get()) == EOF){
		std::cout<<"end"<<std::endl;
	}
	char ret[1000] = {'1','2','3','4','5','6','7'};
	std::cout<<"ret:"<<ret<<std::endl;
	char *rt = ret;
	while((x = fn.peek()) != EOF){
		std::cout<<"--------------------------"<<std::endl;
		std::cout<<"peek:"<<(char)x<<":"<<x<<std::endl;
		std::cout<<"tell1:"<<fn.tellg()<<std::endl;
		std::cout<<rt<<std::endl;
		fn.getline(rt,5,'\n');
		std::cout<<rt<<std::endl;
		std::cout<<rt+4<<std::endl;
		std::cout<<rt+5<<std::endl;
		std::cout<<rt+6<<std::endl;
		int num = fn.gcount();
		std::cout<<"num:"<<num<<std::endl;
		std::cout<<"tell2:"<<fn.tellg()<<std::endl;
//		fn.seekg(1,std::ios::cur);
		rt = rt +  num -1;
	}
	std::cout<<"--------------------------"<<std::endl;
	std::cout<<ret<<std::endl;
	std::cout<<std::endl;
	char t[] = "abc\0cba";
	std::cout<<sizeof(t)<<std::endl;
	std::cout<<strlen(t)<<std::endl;
	return 0;
}
