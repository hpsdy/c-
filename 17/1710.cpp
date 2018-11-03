#include<bitset>
#include<iostream>
int main(){
	unsigned int n = 1 | (1<<2) | (1<<3) | (1<<5) | (1<<8) | (1<<13) | (1<<21);
	std::bitset<32> m;
	m.set(0);
	m.set(2);
	m.set(3);
	m.set(5); 
	m.set(8); 
	m.set(13); 
	m.set(21);
	std::bitset<32> x(n);
	std::cout<<x<<std::endl;
	std::cout<<sizeof(n)<<std::endl;
	std::cout<<n<<std::endl;
	std::cout<<"xxxxxxxxxxxxxxxxxxxxxx"<<std::endl;
	std::cout<<m<<std::endl;
	std::cout<<sizeof(m)<<std::endl;
	std::cout<<m.to_ulong()<<std::endl;
	std::cout<<(m & m)<<std::endl;
	return 0; 
}
