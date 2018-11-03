#include<cstdio>
class t{
	public:
	t(){
		printf("t\n");
	}
   	virtual void x(){
		printf("tx\n");
		//printf("tx:%d\n",xxx);
	}
//	int xxx;
};
class t1:public t{
	public:
	t1(){
//		xxx = x;
		printf("t1\n");
	}
	virtual void x(){
		//printf("t1x:%d\n",xxx);
		printf("t1x\n");
	}
};
int main(){
	int x = 10;
	t *t11 = 0;
	t11->x();
	return 0;
}
