#include<iostream>
template<typename T>

class test{
public:
	test(T);
};
template<typename T> test<T>::test(T a){
	std::cout<<a<<std::endl;
}
