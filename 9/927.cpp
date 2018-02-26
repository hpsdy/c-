#include"head.h"
int main(){
	forward_list<int> fl;
	int num;
	while(cin>>num){
		fl.push_front(num);
	}
	for(auto b=fl.begin(),pre=fl.before_begin();b!=fl.end();){
		if(*b & 1){
			b = fl.erase_after(pre);
		}else{
			pre = b;
			++b;
		}
	}
	for(auto &c:fl){
		cout<<c<<endl;
	}

	return 0;
}
