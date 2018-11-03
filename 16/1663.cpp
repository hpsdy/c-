#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
template<typename T>
std::size_t pe_count(const std::vector<T>& p2,const T& p1){
	std::size_t count = 0;
	for(auto &c:p2){
		if(p1==c){
			count += 1;
		}
	}
	return count;
}
template<>
std::size_t pe_count(const std::vector<const char*>& p2,const char *const &p1){
	std::size_t count = 0;
	for(auto &c:p2){
		if(strcmp(p1,c)){
			count += 1;
		}
	}
	printf("sx size:%d\n",count);
	return count;
}
int main(){
	std::vector<std::string> a1 = {"a","b","a","a","c"};
	std::string a="a";
	printf("string size:%d\n",pe_count(a1,a));
	std::vector<double> a2 = {10,20,10,1,1};
	printf("double size:%d\n",pe_count(a2,10.0d));
	std::vector<int> a3 = {1,1,2,1,1,1,1};
	printf("int size:%d\n",pe_count(a3,1));
	std::vector<const char*> a4 = {"123","321","123"};
	pe_count<const char*>(a4,"123");

	return 0;


}
