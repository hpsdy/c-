#include"head.h"
#include<list>
#include<deque>
int main(){
	list<deque<int>> list_a;
	int n=0;
	int i=0;
	deque<int> tmpdeque;
	while(cin>>n){
		++i;
		if(i>4){
			list_a.push_back(tmpdeque);
			tmpdeque.clear();
			i=0;
		}else{
			tmpdeque.push_back(n);			
		}
	}
	for(const auto &c:list_a){
		for(const auto &ic:c){
			cout<<ic<<'\t';
		}
		cout<<endl;	
	}
	return 0;

}
