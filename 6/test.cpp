#include"head.h"
int main(){
	//char a[] = {'1','2','3'};
	int a[] = {1,2,3};
	int *pt = a;
	int **p = &pt;
	cout<<typeid(a).name()<<endl;
	cout<<typeid(pt).name()<<endl;
	cout<<typeid(p).name()<<endl;
	//string ret = *p;
	//string rett = pt;
	//string pret = a;
	//cout<<ret+pret+rett<<endl;
	return 0;
	char str[] = {'1','2','3','\0'};
	int num[] = {1,2,3};
	cout<<num<<endl;
	cout<<&num<<endl;
	cout<<&num[0]<<endl;
	cout<<*&num[0]<<endl;
	cout<<str<<endl;
	cout<<&str<<" "<<**&str<<endl;
	cout<<&str[0]<<endl;
	cout<<*&str[0]<<" "<<*str<<endl;
	cout<<static_cast<void *>(&str[0])<<endl;

	return 0;
}
