#include<cstdio>
template<typename... args> struct sum;
template<typename T,typename... args> 
struct sum<T,args...>{
	enum{value = sum<T>::value + sum<args...>::value};
};
template<typename T>
struct sum<T>{
	enum{value = sizeof(T)};
};
template<>
struct sum<>{
	enum{value = 0};
};

int main(){
	sum<int,char,double> num;
	sum<> onum;
	printf("size:%d\n",num.value);
	printf("size:%d\n",onum.value);
	return 0;
}
