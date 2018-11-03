#include<cstdio>
//int x = 999;
//x = 1099;
namespace a{
	int x = 10;
	int dh = 1000;
	class test{
		public:
//		int x = 99;
		int xt();
	};
	namespace in{
		class test{
			public:
			test(){
				printf("good contruct\n");
			}
			void p(){
				printf("good test\n");
			}

		};
		int qh = 100;
		void print1(test a){
			a.p();
		}
		void print2(int a){
			printf("int:%d\n",qh);
		}

	}
}
void print3(){
	using namespace a;
	printf("print3:%d\n",dh);
}
int x = 1099;
int a::test::xt(){
	printf("a:%d\n",x);
}
int main(){
	a::test b = a::test();
	b.xt();
	printf("==========\n");
	::a::in::test x = ::a::in::test();
	print1(x);
	//print2(::a::in::qh);		
	print3();		
	printf("lastx:%d\n",dh);
	return 0;
}
