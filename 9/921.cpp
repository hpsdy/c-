#include"head.h"

int main(){
	vector<int> arr={1,2,3,4,5,6};
	auto bp = arr.begin();
	auto ep = bp;
	vector<int> arr1(bp,ep);
	cout<<*bp<<" "<<*ep<<endl;
	cout<<*(arr.erase(bp,ep))<<endl;
	for(auto &c:arr){
		cout<<c<<endl;
	}
	return 0;
	vector<int> ivt;
	vector<int>::iterator b = ivt.begin();
	int i;
	while(cin>>i){
		b = ivt.insert(b,i);
	}
	for(const auto &c:ivt){
		cout<<c<<'\t';
	}	
	cout<<"======="<<endl;
	cout<<ivt.front()<<endl;
	cout<<*(ivt.begin())<<endl;
	cout<<ivt[10]<<endl;
	//cout<<ivt.at(10)<<endl;
	cout<<endl;
	return 0;
}
