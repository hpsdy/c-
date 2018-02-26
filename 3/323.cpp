#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main(){
	int in;
	vector<int> txt;
	cout<<txt.empty()<<" "<<txt.size()<<endl;
	while(cin>>in){
		txt.push_back(in);
	}
	for (auto it=txt.begin();it!=txt.end();++it){
		*it *= 2;
	}
	for (auto it:txt){
		cout<<it<<endl;
	}
	return 0;
}
