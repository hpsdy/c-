#include"head.h"
int main(){
	
	char p[] = {'a','b','\0'};
	char cp[] = {*strdup(&p[0]),*strdup(&p[1]),*strdup(&p[2])};
	char pp[] = {p[0],p[1],p[2]};
	cout<<p<<endl;	
	cout<<cp<<endl;	
	cout<<pp<<endl;	
	cout<<equal(begin(p),end(p),begin(cp))<<endl;
	cout<<equal(begin(p),end(p),begin(pp))<<endl;
	return 0;
}
