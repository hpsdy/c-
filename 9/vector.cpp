#include"head.h"
#include<list>
int main(){
	list<int> arr{1,2,3,4,5};
	//list<int>::iterator p = arr.begin();
	//list<int>::iterator  ep = arr.end();
	for(list<int>::reference c:arr){
		c = 100;
	}
	for(list<int>::value_type c:arr){
		cout<<c<<endl;
	}

	return 0;
}
