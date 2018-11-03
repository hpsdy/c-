#include<stdexcept>
#include<cstdio>
#include<cstdlib>
class test{
	public:
		test() try:data(new char[10000000000]){
			printf("contruct\n");
		}catch(std::bad_alloc e){
			printf("error:%s\n",e.what());
			abort();
		}
	private:
		char *data;

};
int main(){
	typedef void (*p)(int a);
	test();
	return 0;
}
