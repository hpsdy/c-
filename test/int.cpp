#include<iostream>
#include<limits>
#include<string>
using namespace std;
int main(){
	int64_t a=99999;
	cout<<a<<endl;
	cout<<sizeof(a)<<endl;
	cout<<(numeric_limits<int64_t>::max)()<<endl;
	enum ab {W,X=10,Y};
	ab b=X;
	cout<<b<<endl;
	cout<<X<<endl;
	cout<<W<<endl;
	cout<<"===================="<<endl;
	string s="abc秦瀚";
	cout<<"xxxyyy"<<ends;
	printf("%9.6s",s.c_str());
	return 0;
}
