#include"head.h"
int main(){
	int a[] = {1,11,22,33,44,55,66,77,88,99};
	vector<int> vc(begin(a),end(a));
	list<int> lc(begin(a),end(a));
	auto vcb = vc.begin();
	auto vce = vc.end();
	auto lcb = lc.begin();
	auto lce = lc.end();
	while(vcb!=vce){
		if(!(*vcb & 1)){
			vcb = vc.erase(vcb);
			continue;
		}
		++vcb;
	}
	while(lcb!=lce){
		if(*lcb & 1){
			lcb = lc.erase(lcb);
			continue;
		}
		++lcb;
	}
	for(auto &c : vc){
		cout<<c<<endl;
	}
	cout<<"==============="<<endl;
	for(auto &c: lc){
		cout<<c<<endl;
	}
	return 0;
}
