#include"head.h"
void straight_insert_sort(vector<int> arr){
	
	for(auto b = arr.begin()+1;b!=arr.end();++b){
		if(*b<*(b-1)){
			auto x = *b;
			*b = *(b-1);  
			auto j = b-1;
			while(arr.begin()!=j && x<*(j-1)){
				*j = *(j-1);
				--j;	
			}
			*j = x;
		}
	}
	for(auto &c:arr){
		cout<<c<<'\t';
	}
	cout<<endl;
}
typedef vector<int>::iterator ite;
ite minx(ite b,ite e){
	auto mint = b;
	while(b!=e){
		if(*b<*mint){
			mint = b;
		}
		++b;
	}
	return mint;
}
void sample_select_sort(vector<int> arr){
	for(auto b=arr.begin();b!=arr.end();++b){
		auto m = minx(b,arr.end());
		if(b!=m){
			auto tmp = *m;
			*m = *b;
			*b = tmp;
		}
	}
	for(auto &c:arr){
		cout<<c<<'\t';
	}	
	cout<<endl;
}
void quick_sort(vector<int> arr,ite b,ite e){
	auto size = arr.size();
	auto mid = size/2;
		
}
int main(){
	vector<int> arr={2,1,2,3,4,5,7,3,4,6,8,9,10,22,32,15,54};
	straight_insert_sort(arr);
	cout<<"=================="<<endl;
	sample_select_sort(arr);
	return 0;
}
