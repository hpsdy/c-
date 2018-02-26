#include"head.h"
inline void print(){
	cout<<"inline func"<<endl;
}
inline void print(){
	cout<<"inline func"<<endl;
}

constexpr size_t scale(size_t num){
	return num*100;
} 
int main(int argc,char * argv[]){
	print();
	print();
	constexpr int num = 10;
	cout<<"num:"<<num<<endl;
	constexpr size_t n=999;
	constexpr size_t t1 = scale(n);
	constexpr size_t t2 = scale(1000);
	cout<<t1<<endl;
	cout<<t2<<endl;
	return 0;
}
