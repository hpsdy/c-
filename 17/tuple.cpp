#include<tuple>
#include<string>
#include<cstdio>
int main(){
	typedef std::tuple<int,double,std::string> xarr;
	xarr a{10,10.12,"abc"};
	std::size_t size = std::tuple_size<xarr>::value;
	std::tuple_element<1,xarr>::type index = std::get<1>(a);
	printf("size:%d,int:%lf\n",size,index);
	return 0;
}
