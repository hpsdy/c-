#include<new>
#include<cstdlib>
#include<cstdio>
void * operator new(std::size_t size){
	printf("all new:%d\n",size);
	return malloc(size);
}
void * operator new[](std::size_t size){
	printf("all new[]:%d\n",size);
	return malloc(size);
}

class tn{
	public:
		void * operator new(std::size_t size){
			printf("tn new:%d\n",size);
			return ::operator new(size);
		}
		void * operator new[](std::size_t size){
			printf("tn new[]:%d\n",size);
			return ::operator new[](size);
		}

};

int main(){
	tn *a = new tn[10]();		
	tn *b = new tn();		

	return 0;
}
