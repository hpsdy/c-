#include"head.h"
void sx(int *x,int *y){
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
int main(){
	int x=998,y=889;
	cout<<x<<" "<<y<<endl;	
	sx(&x,&y);	
	cout<<x<<" "<<y<<endl;	
	return 0;
}
