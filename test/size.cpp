#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int64_t num=10;
	cout<<sizeof(num)<<endl;
	cout<<(sizeof(num)<<3)<<endl;
	cout<<((sizeof(num)<<3)-1)<<endl;
	cout<<(~(1LLU<<((sizeof(num)<<3)-1)))<<endl;
	return 0;
}

