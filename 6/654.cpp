#include"head.h"
int jia(const int &x,const int &y){
	return x+y;
}
int jian(const int &x,const int &y){
	return x-y;
}
int cheng(const int &x,const int &y){
	return x*y;
}
int chu(const int &x,const int &y){
	return x/y;
}



int main(){
	typedef decltype(jia) *p;
	vector<p> arr;
	arr.push_back(jia);
	arr.push_back(jian);
	arr.push_back(cheng);
	arr.push_back(chu);
	int x=10,y=20;
	for(const auto &c:arr){
		cout<<c(x,y)<<endl;
	}
	return 0;
}
