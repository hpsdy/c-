#include<cstdio>
#include<typeinfo>
template<typename T>
void t(T &&t) {
	printf("type:%s\n", typeid(T).name());
}
void p(int n) {
	printf("n:%d\n", n);
}
int main() {
	int a = 10;
	int &b = a;
	int &c = b;
	t(a);
	t(b);
	t(c);
	p(a);
	p(b);
	p(c);
	printf("%p:%p:%p\n", &a, &b, &c);
	return 0;
}
