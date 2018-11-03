#include<cstdio>
#include<vector>
template<typename T>
auto p(T b,T e)->decltype(*b){
	return *b;
}
int main(){
	std::vector<int> arr{1,2,3,4,5};
	auto x = p(arr.begin(),arr.end());
	printf("%d",x);
	return 0;
}
