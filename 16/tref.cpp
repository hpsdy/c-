#include<cstdio>
template<typename T>
void p(T & t){
	printf("%d\n",t);
}
int main(){
	p<const int>(10);
}

