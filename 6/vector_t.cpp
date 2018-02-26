#include"head.h"
int main(){
	vector<int> arr = {1,2,3,4};
	for(const auto &c:arr){
		cout<<c<<endl;
	}
	auto b = arr.begin();
	cout<<arr[0]<<endl;
	cout<<*(b+1)<<endl;
	return 0;
}
