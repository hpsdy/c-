#include<cstdio>
#include<initializer_list>
#include<utility>
template<typename F,typename... args>
void expand(const F &f,args&&... rest){
	std::initializer_list<int>{(f(std::forward<args>(rest)),0)...};
}
int main(){
	expand([](int i){printf("%d\n",i);},1,2,3,4,5);
	return 0;
}
