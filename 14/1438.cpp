#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>
class checkString {
  public:
    checkString(std::size_t size): sz(size) {}
    bool operator()(const std::string &str) {
        return str.size() == sz;
    }
  private:
    std::size_t sz;
};

int main(int argc, char const *argv[])
{
		
/*	std::ifstream in("string.txt",std::ios::in|std::ios::binary);
//	char buf[3] = {'\0'};
	char buf[3];
	char c;
	std::cout<<"tellg1:"<<in.tellg()<<std::endl;
	while((c=in.peek())!=EOF){
		in.read(buf,3);
		std::cout<<"peek1:"<<c<<std::endl;
		std::cout<<"buf1:"<<buf<<std::endl;
		std::cout<<"count1:"<<in.gcount()<<std::endl;
	}
	std::cout<<"========="<<std::endl;
	std::cout<<"tellg2:"<<in.tellg()<<std::endl;
	in.clear();
	in.seekg(0);
	std::cout<<"tellg2:"<<in.tellg()<<std::endl;
	std::string str;
	std::stringstream strIo;
	while(getline(in,str)){
		std::cout<<"ori string2:"<<str<<":"<<str.size()<<std::endl;
		std::cout<<"str1 state:"<<strIo.rdstate()<<std::endl;
	//	strIo.clear();
		std::cout<<"str2 state:"<<strIo.rdstate()<<std::endl;
	//	strIo.ignore();
		std::cout<<"str3 state:"<<strIo.rdstate()<<std::endl;
		std::cout<<"str3 state:"<<strIo.eof()<<std::endl;
		strIo.str(str);
		std::string instr;
		std::cout<<"str4 state:"<<strIo.rdstate()<<std::endl;
		while(strIo>>instr){
			std::cout<<"instr state:"<<strIo.rdstate()<<std::endl;
			std::cout<<"string2:"<<instr<<":"<<instr.size()<<std::endl;
		}
	}
	std::cout<<"========="<<std::endl;
	std::cout<<"tellg3:"<<in.tellg()<<std::endl;
	in.clear();
	in.seekg(0,std::ios::beg);
	std::cout<<"tellg3:"<<in.tellg()<<std::endl;
	char x;
	while((c=in.peek())!=EOF){
		std::cout<<"tellg3:"<<in.tellg()<<std::endl;
		x = in.get();
		std::cout<<"x3:"<<x<<std::endl;
	}
	std::cout<<"========="<<std::endl;
*/
	std::string str;
	std::cin>>str;
	std::cout<<str<<std::endl;	
	std::cin.ignore(3,'q');
	std::cin>>str;
	std::cout<<str<<std::endl;	

	std::cout<<"==="<<std::endl;	
	std::cin.ignore(4,'q');
	
	return 0;
}
