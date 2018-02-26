#include"head.h"
int sum(int n){
	static int sumx=0;
	while(n>0){
		sumx +=n;
		--n;
	}
	int tmp = sumx;
	sumx=0;
	return tmp;
}
int xsum(int n){
	static int sumx = 0;
	if(n>0){
		return xsum(n-1)+n;		
	}else{
		return 0;
	}	
}
int main(){
	cout<<sum(10)<<endl;
	cout<<xsum(10)<<endl;
	return 0;
}
