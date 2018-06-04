#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
int compare(const void *a,const void *b){
	return *(int*)b-*(int*)a;
}
int main(){
	int arr[10]={0,1,2,3,4,5,6,7,8,9};
	cout<<sizeof(arr)/sizeof(int)<<endl;
	qsort(arr,10,sizeof(int),compare);
	for(auto c:arr){
		cout<<c<<endl;
	}	
	return 0;
}
