#include<iostream>
#include<set>
#include<memory>
using namespace std;
int main(){
	shared_ptr<set<int>> a(new set<int>({1,2,3}));
	for(const auto &c:*a){
		cout<<c<<endl;
	}
}
