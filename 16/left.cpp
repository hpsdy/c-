#include<cstdio>
#include<utility>
void p(int && n){
	printf("%d\n",n);
}
int main(){
	p(10);
	int a=20;
	p(std::move(a));
	return 0;
}
