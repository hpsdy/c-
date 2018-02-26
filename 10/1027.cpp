#include"head.h"
#include<iterator>
int main(){
	vector<int> ints = {1,9,8,7,6,3,2,3,4,2,3,4};
	sort(ints.begin(),ints.end());
	vector<int> li;
	auto ep = unique_copy(ints.begin(),ints.end(),back_inserter(li));
	//auto ep	= unique(ints.begin(),ints.end());
	cout<<"ep:"<<typeid(ep).name()<<endl;
	ep=9999;
	for(auto &c:li){
		cout<<c<<'\t';
	}
	cout<<endl;
	for(auto &c:ints){
		cout<<c<<'\t';
	}
	cout<<endl;
	return 0;
}
