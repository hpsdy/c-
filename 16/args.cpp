#include<cstdio>
int num = 0;
template<typename T> void p(T a);
template<typename T>
void p123(T a){
	++num;
	printf("%d 1->a:%d\n",num,a);	
}
template<typename T,typename... args>
void p(T a,const args... rest){
	++num;
	printf("%d 2->a:%d,size:%d\n",num,a,sizeof...(rest));
	p(rest...);
}
template<typename T>
void p(T a){
	++num;
	printf("%d 1->a:%d\n",num,a);	
}

int main(){
	p(1,2,3,4,5,6,7,8);
	return 0;
}
