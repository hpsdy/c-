#include"screen.h"
int main(){
	mgr xxx;
	xxx.get(0).display(cout);
	xxx.clear(0);
	xxx.get(0).display(cout);
	return 0;
	screen three;
	three.display(cout);
	return 0;
	const screen two(5,8,'w');
	two.display(cout);
	screen one(3,5,'h');
	one.display(cout);
	one.move(2,4).set('#').display(cout);
	//vector<screen> screens{screen(10,20,'h')};
	return 0;
}
