#include<memory>
#include<string>
#include<cstdio>
void test() {
	int *arr = new int[10];
	std::string *str = new(arr) std::string("hello world");
	printf("str:%s\n", str->c_str());
	using std::string;
	//str->~string();
	//::operator delete(str);
}

int main() {
	test();
}
