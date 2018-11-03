#include<cstdio>
#include<string>
#include<iostream>
#include<utility>
template<typename T>
void print(T && str){
	std::cout<<str<<std::endl;
}


template<typename T1,typename... T2>
void print(T1 && s1,T2&&... s2){
	std::cout<<s1<<std::endl;
	print(std::forward<T2>(s2)...);
}
int main(){
	print(1,2,3,4,5);
	return 0;
}
