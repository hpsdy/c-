#include <cstdlib>
#include <cstring>
namespace func{
	char *split_char(char *&str,const char *split){
		if(nullptr==str || nullptr==split){
			return nullptr;
		}
		char *start = str;
		char *end = std::strstr(str,split);
		std::size_t len=std::strlen(split);
		if(len>0 && end!=nullptr){
			*end='\0';
			end+=len;
		}
		str=end;
		return start;
	}


}
