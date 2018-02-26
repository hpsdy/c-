#include"head.h"
class myStatic{
	public:
	void print(){
		cout<<num<<"-"<<str<<endl;
	}
	int sum(){
		int n = num;
		static int sumx=0;
		while(n>0){
			sumx += n;
			--n;
		}
		return sumx;
	}
	void p(const int n){
		cout<<"p:"<<n<<endl;
	}
	static void hello(){
		cout<<"hello world"<<endl;
	}
	public:
	string str="hello world";
	static const  int num=100;
	//static constexpr int num=999;
	static int init(){
		return 100;
	}
	public:
	const int xy=999;
	int ab = xy;
	int cc[num] = {};

};
const int myStatic::num;

void ps(const int &x){
	cout<<"ps:"<<x<<endl;
}
int main(){
	myStatic one;
	one.print();
	cout<<one.sum()<<endl;
	cout<<one.xy<<endl;
	cout<<myStatic::num<<endl;
	cout<<one.num<<endl;
	one.p(myStatic::num);
	ps(myStatic::num);
	const int a=100;
	const int b=a;
	cout<<&a<<endl;
	cout<<&b<<endl;
	myStatic::hello();
	//cout<<myStatic::xy<<endl;
	return 0;
}

