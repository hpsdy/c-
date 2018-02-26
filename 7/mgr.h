#ifndef MGR
#define MGR
#include"screen.h"
class mgr{
	public:
	typedef vector<screen>::size_type pos;
	mgr()=default;
	void clear(pos index){
		screen &p = screens[index];
		p.contents = "xyz";	
	}
	screen & get(pos index){
		return screens[index];
	}
	private:
	vector<screen> screens{screen(5,5,'o')};
};
#endif
