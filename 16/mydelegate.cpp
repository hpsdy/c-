#include<cstdio>
#include<utility>
template<typename T,typename R,typename... Args>
class mydelegate{
	public:
	mydelegate(T* t,R (T::*f)(Args...)):mt(t),mf(f){}
	R operator()(Args&&... args){
		return (mt->*mf)(std::forward<Args>(args)...);
	}

	private:
	T *mt;
	R (T::*mf)(Args...);
};
template<typename T,typename R,typename... Args>
mydelegate<T,R,Args...> createDelegate(T *t,R (T::*f)(Args...)){
	return mydelegate<T,R,Args...>(t,f);
}

class test{
	public:
	void func(int a,int b,int c,int d){
		printf("sum:%d\n",a+b+c+d);
	}

};
int main(){
	test t;
	auto f = createDelegate(&t,&test::func);
	f(10,20,99,100);
	return 0;

}
