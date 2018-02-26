#include"head.h"
int main(){
	int j = 0;
	constexpr int i = 2;
	constexpr const int *p = &i; // const pointer, const data
	constexpr int *p1 = &j; // const pointer, non-const data
	return 0;
}
