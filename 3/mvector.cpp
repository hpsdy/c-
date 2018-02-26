#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main(){
	string in;
	vector<string> a(10);
	cout<<a.empty()<<" "<<a.size()<<endl;
	while(cin>>in){
		a.push_back(in);
	}
	for (auto c:a){
		cout<<c<<endl;
	}
	return 0;
}
