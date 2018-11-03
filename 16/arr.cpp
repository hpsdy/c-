#include<cstdio>
#include<iostream>
int main(){
	char arr[4][29];
	printf("size:%d\n",sizeof(arr));
	char *brr = &arr[3][0];
	char x[] = "123";
	snprintf(brr,sizeof(x),"%s",x);
	std::string str= brr;
	printf("brr:%s\n",brr);
	printf("str:%s\n",str.c_str());
	//snprintf(brr,sizeof(x),"%s",x);
	std::cout<<(void*)brr<<std::endl;
	std::cout<<(void*)&brr[0]<<std::endl;
	int i=1;
	for(auto &c:arr){
		printf("%d:%s\n",i,c);
		++i;
	}

	return 0;
}
