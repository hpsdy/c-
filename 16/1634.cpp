#include<cstdio>
#include<typeinfo>
template<typename T>
void p(const T& a,const T& b){
	printf("a:%s/b:%s/type:%s\n",a,b,typeid(T).name());
}
void px(const char (&a)[4],const char(&b)[4]){
	printf("a:%s/b:%s/type:%s\n",a,b,typeid(b).name());
}

int main(){
	p("abc","qwf");
	px("abc","qwf");
	return 0;
}
