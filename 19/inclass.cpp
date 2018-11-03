#include<cstdio>
class t1{
	public:
	class ic;
	t1(){
		printf("t1 construct\n");
	}
	typedef int xxx;
	private:
		int a = 100;
		char b= 'c';
		//ic &c;
		static t1 ct1;
};
class t1::ic{
	public:
	ic(){
		xxx num = 2000;
		printf("ic construct:%d\n",num);
	}
};
int main(){
	printf("size t1:%d\n",sizeof(t1));
	t1::ic x;
	return 0;
}
