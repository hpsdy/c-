#include<initializer_list>
#include"head.h"
int ret1[] = {1,2,3,4,5,6,7};
int ret2[] = {7,6,5,4,3,2,1};
typedef int arr[6];
decltype(ret1) * some(const int &num){
	if(num%2){
		for(auto &c:ret1){
			c = c*num;
		}
		return &ret1;
	}
	return &ret2;
}
void print(const int (&arr)[3]){
	for(const auto &c:arr){
		cout<<c<<endl;
	}
}
void print(const int (*arr)[3]){
	cout<<"ptr"<<endl;
	for(const auto &c:*arr){		
		cout<<c<<endl;
	}
}

int main(){
	int num;
	cout<<"please input num:"<<endl;
	cin>>num;	
	auto ret = some(num);
	for(const auto &c:*ret){
		cout<<c<<endl;
	}
	//大小要与形参一致
	int arr[] = {1,2,3};
	print(arr);
	print(&arr);
	const int t = 100;
	const int *w = &t;
	cout<<w<<" "<<&w<<endl;
	cout<<typeid(w).name()<<endl;
	auto t1 = const_cast<int *>(w);
	cout<<w<<" "<<&w<<endl;
	cout<<typeid(w).name()<<endl;
	*t1 = 99;
	cout<<typeid(t1).name()<<endl;
	cout<<t<<" "<<&t<<endl;
	cout<<*t1<<" "<<&t1<<endl;
	cout<<*w<<" "<<&w<<endl;
	const int y = 100;
	const int &z = y;
	cout<<z<<" "<<&z<<endl;
	auto &t2 = const_cast<int &>(z);
	cout<<z<<" "<<&z<<endl;
	t2 = 99;
	cout<<typeid(t2).name()<<endl;
	cout<<y<<" "<<&y<<endl;
	cout<<t2<<" "<<&t2<<endl;
	cout<<z<<" "<<&z<<endl;
	enum xr {XXX,YYY=-10,ZZZ};
	xr wz=XXX;
	cout<<wz<<endl;
	return 0;
}
