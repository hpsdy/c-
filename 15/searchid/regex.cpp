#include<regex>
#include<cstdio>
#include<string>
int main(){
	std::string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]";
	std::regex r(pattern);
	std::smatch results;
	std::string test_str = "hello freid";

}
