#include<stdexcept>
#include<cstdio>
namespace one{
class test{
	public:
	test()try{
		throw std::runtime_error("test");	
	}catch(std::runtime_error &e){
		printf("first:%s\n",e.what());
		printf("over\n");
		//throw;
	}
};
}
//using namespace one;
int main(){
	try{
		one::test();
	}catch(std::exception &e){
		printf("excp:%s\n",e.what());
	}catch(...){
		printf("some exception happen\n");
	}
	return 0;

}
