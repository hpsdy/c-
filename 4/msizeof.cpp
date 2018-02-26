#include"head.h"
int main(){
	
	char str[] = "abc";
	string strs = "abc";
	string arrs[] = {"abc","cba"};
	cout<<"str:"<<(sizeof(str)/sizeof(str[0]))<<endl;
	cout<<"strs:"<<(sizeof(strs))<<",size:"<<strs.size()<<endl;
	cout<<"strs:"<<(sizeof(strs[0]))<<",size:"<<strs.size()<<endl;
	cout<<"arrs:"<<(sizeof(arrs)/sizeof(arrs[0]))<<endl;
	for (auto x:arrs){
		cout<<x<<endl;
	}
	return 0;
	int size;
	cin>>size;
	int arr[10];
	cout<<sizeof(arr)<<endl;
	constexpr size_t n = sizeof(arr);
	cout<<n<<endl;	
	return 0;
}
