#include<cstdio>
#include<typeinfo>
template<typename> class frid;
/*template<typename T> 
class frid{
	public:
		frid(){
			printf("a construct,%s\n",typeid(T).name());
		}
};*/

template<typename T> 
class test{
	friend class frid<T>;
	public:
		test(){
			printf("test construct,%s\n",typeid(T).name());
		}
};
/*template<typename T> 
class frid{
	public:
		frid(){
			printf("a construct,%s",typeid(T).name());
		}
};*/

int main(){
	test<int> obj;
	return 0;
}
template<typename T> 
class frid1{
	public:
		frid1(){
			printf("a construct,%s",typeid(T).name());
		}
};

