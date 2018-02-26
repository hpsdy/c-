#include<iostream>
#include<stdio.h>
using namespace std;
int main(){
	char arr[4];
	int num = sprintf(arr,"%s","aabbbccc");
	cout<<arr<<endl;
	cout<<num<<endl;
	return 0;

}
