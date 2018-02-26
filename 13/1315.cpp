#include<iostream>
#include<string>
using namespace std;
int randNum(){
	return rand()%1000;	
}
class numbered{
	friend void f(const numbered &);
	public:
		numbered(){rn = randNum();cout<<"cons:"<<rn<<endl;}
		numbered(const numbered & n){ cout<<"copy:"<<n.rn<<endl;rn = randNum();}
	private:
		int rn;
		
};
void f(const numbered &p){
	cout<<p.rn<<endl;
}
int main(){
	srand(time(0));
	numbered a,b=a,c=b;
	f(a);f(b);f(c);
//	cout<<a.rn<<endl;
	return 0;	
}
