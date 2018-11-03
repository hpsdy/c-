#include<cstdio>
#include"get_token_str.cpp"
int main(){
	char a[10];
	printf("size:%d\n",sizeof(a));
	a[5] = '\0';
	printf("size:%d\n",sizeof(a));
	char one[] = "abc hello";
	char *x = get_token_str(one,"h\0");
	printf("str:%s\n",x); 
	int32_t x=1000;
	printf("str:%d\n",x); 
	return 0;

}
