#ifndef SCREEN
#define SCREEN
#include"head.h"
class screen;
class mgr{
	public:
	typedef vector<screen>::size_type pos;
	mgr();
	void clear(pos);
	screen & get(pos);
	private:
	vector<screen> screens;
};
void test();
class screen{
	friend void mgr::clear(pos);
	friend void test(){
		cout<<"friend test"<<endl;
	}
	public:
	typedef string::size_type pos;
	screen()=default;
	screen(pos w,pos h,char c):width(w),heigh(h){
		test();
		contents = "";
		for(pos i=0;i<heigh;i++){
			string tmp(w,c);
			tmp +='\n';
			contents += tmp;	
		}
		cout<<contents.size()<<endl;
	}
	char get() const {
		return contents[cursor];
	}
	char get(pos w,pos h);
	screen & set(char c){
		contents[cursor] = c;
		return *this;
	}
	screen & set(pos w,pos h,char c){
		return move(w,h).set(c);
	}
	const screen & display(ostream &o) const {
		o<<"const"<<endl;
		do_display(o);	
		return *this;
	}
	screen & display(ostream &o){
		o<<"no const"<<endl;
		do_display(o);
		return *this;
	}

	screen & move(pos r,pos c);
	void some_num() const;
	private:
	mutable unsigned count=0;
	pos width=0,heigh=0,cursor=0;
	string contents = "screen";
	void do_display(ostream &o) const {
		o<<contents;
	}
};
inline screen & screen::move(pos w,pos h){
	pos row = (h-1) * (width+1);
	cursor = row+(w-1);
	return *this;	
}
inline char screen::get(pos w,pos h){
	return move(w,h).get();
} 
void screen::some_num() const{
	++count;
}
mgr::mgr(){
	screens.push_back(screen(10,5,'z'));
}
void mgr::clear(pos index){
	screen &p = screens[index];
	p.contents = "xyz";	
}
screen & mgr::get(pos index){
	return screens[index];
}
#endif
