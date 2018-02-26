#include"head.h"
/*
 *
 *聚合类
 */
class juhe{
	public:
	/*juhe(int q,int w,int e):a(q),b(w),c(e){
		cout<<"default init"<<endl;
	}*/
	int a;
	int b;
	int c;
	void print() const {
		cout<<a<<b<<c<<endl;
	}
};
int main(){
	constexpr juhe one = {10,20,30};
	//constexpr juhe one{10,20,30};
	one.print();
//	one.a=999;
	//one.print();
	constexpr juhe c = one;
	return 0;
}
