#include <iostream>
#include <memory>
#include <typeinfo>
int main(){
	std::allocator<char> alloc;
	char *p=alloc.allocate(5);
	char *t = p;
	alloc.construct(p++,'a');
	alloc.construct(p++,'b');
	alloc.construct(p++,'c');
 	alloc.construct(p++,'d');
	alloc.construct(p++,'e');
//	std::cout<<typeid(ret).name()<<std::endl;
	while(t!=p){
		std::cout<<*t++<<std::endl;
	}
	return 0;
	

}
