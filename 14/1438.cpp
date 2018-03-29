#include <iostream>
#include <string>
#include <fstream>
#include <stringstream>
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
	std::fstream fn("string.txt",std::fstream::in|std::fstream::out|std::fstream::binary);
	char buf[2];
	while(!fn.eof()){
		auto rtmp = fn.read(buf,3);
		std::cout<<rtmp<<std::endl;
		std::cout<<fn.gcount()<<std::endl;
		auto wtmp = fn.write(buf,3);
		std::cout<<wtmp<<std::endl;
		std::cout<<fn.gcount()<<std::endl;
	}

	return 0;
}