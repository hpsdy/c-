#include"head.h"
#include<iterator>
int main(){
	vector<int> arr = {1,2,0,3,4,5,0,6,7};
	typedef vector<int>::reverse_iterator rite;
	rite e = arr.rbegin();
	rite b = arr.rend();
	while(e!=b){
		cout<<*e<<'\t';
		++e;
	}
	cout<<endl;
	cout<<"===="<<endl;
	auto pos = find(arr.rbegin(),b,0);
	cout<<*pos<<endl;
	--pos;
	cout<<*pos<<endl;
	cout<<"===="<<endl;
	cout<<"a:"<<*e<<endl;
	cout<<"b:"<<*(b-4)<<endl;

	list<int> li(arr.rbegin()+1,b-2);
	print(li);
	return 0;


}
