#include<iostream>
#include<string>
#include<cstring>
using namespace std;
struct home{
	char * name;
	int id;
};
int main(){
	char *alloc_char = new char[100];
	memset(alloc_char,0,100);
	home *h = (home*)alloc_char;
	char xs[] = "qinhan";
	h->name=xs;
	h->id=999;
	char *str = alloc_char+sizeof(home);
	char ss[] = "hello world";
	strcpy(str,ss);
	cout<<"homesize:"<<sizeof(home)<<endl;
	cout<<"ss1:"<<(alloc_char+sizeof(home))<<endl;
	cout<<"ss2:"<<str<<endl;
	cout<<"ssp0:"<<(int*)(alloc_char)<<":"<<static_cast<void*>(alloc_char)<<endl;
	cout<<"ssp1:"<<(int*)(alloc_char+sizeof(home))<<":"<<static_cast<void*>((alloc_char+sizeof(home)))<<endl;
	cout<<"ssp2:"<<(int*)str<<":"<<static_cast<void*>(str)<<endl;
	
	char *copy = alloc_char;
	cout<<"copy:"<<copy<<":"<<sizeof(copy)<<":"<<strlen(copy)<<endl;
	home *ch = (home*)copy;
	cout<<(ch->name)<<":"<<(ch->id)<<endl;
	char *l = copy+sizeof(home);
	cout<<l<<endl;
	return 0;
	

}
