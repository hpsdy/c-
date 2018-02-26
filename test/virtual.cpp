#include<iostream>
#include<string>
using namespace std;
struct base{
	base(){
		cout<<"1contruct"<<endl;
	}
	void print()const{
		cout<<"base print"<<endl;
	}
	
	inline void p()const{
		cout<<"base"<<str<<endl;
	}
	void print(string _str) const {
		cout<<_str<<endl;
	}
	~base(){
		cout<<"1destory"<<endl;
	}

	private:
	string str="qinhan";
};
struct child:public base{
	child(){
		cout<<"2contruct"<<endl;
	}

	void print()const{
		cout<<"child print"<<endl;
	}
	inline void p()const{
		cout<<"child qinhan"<<endl;
	}
	~child(){
		cout<<"2destory"<<endl;
	}


};
struct son:public child{
	son(){
		cout<<"3contruct"<<endl;
	}

	void print()const{
		base::p();
		cout<<"son print"<<endl;	
	}
	void print(string str){
		cout<<str<<endl;
	}
	~son(){
		cout<<"3destory"<<endl;
	}
};
int main(){
	const base &p1 = base();
	p1.print();
	cout<<"=========="<<endl;
	const base &p2 = child();
	p2.print();
	cout<<"=========="<<endl;
	const son &p3 = son();
	p3.print();
//	p3.print("xxxyyy");
	cout<<"=========="<<endl;
	return 0;
}
