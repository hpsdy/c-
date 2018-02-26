#include"head.h"
#include<iterator>
int main(){
	istream_iterator<int> ci(cin);
	istream_iterator<int> en;
	cout<<*ci<<endl;
	auto tmp = ci;
	++ci;
	cout<<*ci<<endl;
	cout<<*tmp<<endl;
	++ci;
	cout<<*ci<<endl;
	++ci;
	cout<<*ci<<endl;
	++ci;
	cout<<*ci<<endl;
	cout<<"==========="<<endl;
	cout<<*tmp<<endl;
	cout<<*++tmp<<endl;
	cout<<"==========="<<endl;
	while(tmp!=en){
		cout<<*tmp<<'\t';
		++tmp;
	}
	cout<<endl;
	return 0;

}
