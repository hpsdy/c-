#include"head.h"
/*
 *explicit抑制了类类型的自动转化过程。
 *在没有explicit修饰的情况下，只有一个实参的构造函数会把实参类型自动转化为类类型。
 *编译器的自动转化只会发生一步。“abc”-》string-》class是两步。
 *explicit（明确的）,只能在类内部声明.
 */
class someConv{
	public:
	explicit someConv(string str){
		cout<<"some conv happen:"<<str<<endl;
	}
};
int main(){
	string stx = "abc";
	//someConv str=string("abc");
	someConv str("abc");
	return 0;
}

