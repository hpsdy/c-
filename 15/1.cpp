#include<iostream>
using namespace std;
class base{
	public:
		base(){
			cout<<"base construct"<<endl;
		}
		~base(){
			cout<<"base destroy"<<endl;
		}
};
class son:public base{
	public:
		son(){
			cout<<"son construct"<<endl;
		}
		~son(){
			cout<<"son destroy"<<endl;
		}
};
int main(){
	son *one = new son();
	delete one;
	return 0;

}
