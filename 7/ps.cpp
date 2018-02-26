#include"person.h"
int main(){
	person one;
	one.name="秦瀚";
	one.addr="海淀";
	cout<<one.getname()<<":"<<one.getaddr()<<endl;
	return 0;
}
