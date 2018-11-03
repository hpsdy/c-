#include<cstdio>
#include<new>

class t1{
	//int a = 0;
	//int x = 0;
	//int y = 0;
	//int w = 0;
	//int w1 = 0;
	//int w2 = 0;
	public:
	t1(){
		printf("t1 construct\n");
	}
	virtual ~t1(){
		printf("t1 destroy\n");
	}
	/*void operator delete(void *p) noexcept {
		printf("t1 delete\n");
		::operator delete(p);
	}*/
};
class t2:public t1{
	int b = 0;
	int c = 0;
	public:
	t2(){
		printf("t2 construct\n");
	}
	virtual ~t2(){
		printf("t2 destroy\n");
	}
	void operator delete(void *p,size_t num) noexcept {
		printf("t2 delete:%d\n",num);
		::operator delete(p);
	}
};
int main(){
	int y=100;
	printf("int size:%d\n",sizeof(int));
	printf("t1 size:%d\n",sizeof(t1));
	printf("t2 size:%d\n",sizeof(t2));
	return 0;
	t1 *x1 = new t2();
	printf("* size:%d\n",sizeof(x1));
	delete x1;
	printf("=================\n");
	t2 *x2 = new t2();
	delete x2;
	return 0;

}
