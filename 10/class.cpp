#include"head.h"
void p();
struct P;

int main(){
	p();
	P();
	return 0;

}
void p(){
	cout<<"p"<<endl;
}
struct P{
	P(){
		cout<<"class P"<<endl;
	}

};

