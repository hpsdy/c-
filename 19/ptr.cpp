#include<cstdio>
class test{
	public:
	test(int a){
		printf("xxx\n");
	}
	test(){
		printf("ooo\n");
	}

	test(const test &p){
		printf("zzz\n");
	}

	~test(){
		printf("yyy\n");
	}
	private:
	int n=100;
};
int main(){
	test arr[3] = {test(10),20};
	int *ptr = new int(10);
	(void)(ptr);
	//test * t=new test();
//	(void)(t);
	printf("wo ai ni\n");
//	delete t;
	return 0;	

}
