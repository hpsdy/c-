#include<iostream>
#include<vector>
#include<memory>
using namespace std;
int main(){
	vector<int> num{1,2,3,4,5,6,7,8,9};
	allocator<int> alloc;
	int *p = alloc.allocate(num.size()*2);
	int *cp = p;
	cp = uninitialized_copy(num.begin(),num.end(),cp);
	uninitialized_fill_n(cp,num.size(),100);
	cp += num.size();	
	while(cp!=p){
		cout<<*(--cp)<<endl;
	}
	return 0;
}
