#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class test{
	public:
	test(){
		cout<<"parent construct"<<endl;
	}
	virtual ~test(){
		cout<<"parent destroy"<<endl;
	}
};
class son:public test{
	public:
	son(){
		cout<<"son construct"<<endl;
	}
	~son(){
		cout<<"son destroy"<<endl;
	}
	void p(){
		cout<<"son print"<<endl;
	}
};
int main(){
	vector<shared_ptr<test>> arr;
	shared_ptr<son> p1(new son);
	shared_ptr<son> p2(p1);
	son * p3 = &(*p1);
	cout<<"num:"<<p1.use_count()<<endl;
	shared_ptr<son> p4;
	if(p4){
		cout<<"find"<<endl;
	}else{
		cout<<"unknow"<<endl;
	}
	weak_ptr<son> p5(p4);
	auto p6 = p5.lock();
	if(p6){
		p6->p();
	}	
	return 0;

}
