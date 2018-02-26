#include<stdio.h>
#define XY() \
const char *one##eq="123"
//const char *oneew="world";
int main(){
	XY();
	printf(oneeq);
	return 0;
}
