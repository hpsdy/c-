#include"head.h"
int compare(int x,const int *y){
	if(x>*y){
		return x;
	}else{
		return *y;
	}

}
int main(){
	int i = 100;
	cout<<compare(10,&i)<<endl;	
	return 0;
}
