#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main(){
	int in;
	vector<int> a;
	cout<<a.empty()<<" "<<a.size()<<endl;
	int init=0,i=1;;
	while(cin>>in){
		a.push_back(in);
		if(i==2){
			cout<<"count:"<<a[init]+a[init-1]<<endl;	
			i=1;
		}else{
			++i;
		}
		++init;
	}
	auto size = a.size();
	for (decltype(size) index=0;index<size/2;index++){
		cout<<"index:"<<index<<","<<size-index-1<<endl;
		cout<<"int:"<<a[index]<<","<<a[size-index-1]<<endl;
		cout<<"step_1 count:"<<a[index]+a[size-index-1]<<endl;
	}
	return 0;
}
