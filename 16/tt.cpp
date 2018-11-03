#include<cstdio>
#include<vector>
#include<string>
#include<typeinfo>
template<typename T>
std::vector<T> t(const T a){
	printf("type:%s\n",typeid(T).name());
	return std::vector<T>{a};
}


int main(){
	auto a = t("abc");
	for(auto c:a){
		printf("%s\n",c);
	}
	return 0;
}
