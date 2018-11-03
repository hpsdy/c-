#include<cstdio>
#include<ctime>

class t0{
	public:
	t0(){
		printf("t0\n");
	}
};

class t1{
	public:
	t1(){
		printf("t1\n");
	}
	t1(int n){
		printf("txn:%d\n",n);
		num = n;
	}
	int num = 100;
	int x = 11;
};
class t2:public virtual t1{
	public:
	t2():t1(102){
		printf("t2\n");
	}
	t2(int n){
		printf("t2n:%d\n",n);
	}
	//int x = 22;

	int num = 200;
};
class t3:public virtual t1{
	public:
	t3():t1(103){
		printf("t3\n");
	}
	t3(int n){
		printf("t3n:%d\n",n);
	}
//	int x = 33;
	int num = 300;
};
/*class t4:public t2{
	public:
	t4(){
		printf("t4\n");
	}
};*/
class base:public t2, public t3{
	public:
	base():t2(9999),t3(8888),t1(7777){
		printf("base\n");
	//	printf("base:%d\n",t1::num);
	}
	int num = 999;

};

int main(){

	base *x1 = new base();
	printf("qinhan:%d\n",x1->x);
	printf("xxxxxxxxxxxxxxxxxx\n");
	t2 x2;
	t3 x3;
	return 0;
}
