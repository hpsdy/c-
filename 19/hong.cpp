#include<cstdio>
#include<cstring>
#if !(defined(xxx))
	#define xxx printf("one\n")
#endif
#if !(defined(xxx))
	#define xxx printf("two\n")
#endif
#define class testw{ \
	public: \
	testw(){ \
		printf("sonme test\n"); \
	} \
};
#define	void func_testw(){ \
		printf("func test\n"); \
	}
int main(){
	int ax[5] = {100,99,1,2,3};
//	int * ax = new int[5]{1,2,3};
	memset(ax,-1,20);
	printf("size:%d\n",sizeof(ax));
	for(int i=0;i<5;++i){
		if(ax[i]==0){
			printf("xinfo\n");
		}else{
			printf("info:%d\n",*(ax+i));
		}
	}
	xxx;
	return 0;
}
