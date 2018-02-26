#ifndef HEAD
#define HEAD
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<typeinfo>
#include<cctype>
#include<cstddef>
#include<stdexcept>
#include<list>
#include<deque>
#include<array>
#include<sstream>
#include<fstream>
#include<forward_list>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<map>
#include<set>
using namespace std;
template<typename T1,typename T2>
T1 &myread(const string &str,T1 &t,T2 i){
	ifstream fn(str);
	if(fn){
		T2 ctype;
		while(fn>>ctype){
			t.push_back(ctype);
		}	
		fn.close();		
		return t;
	}else{
		throw invalid_argument("invalid params:"+str);
	}
}
template<typename T>
void print(T &t){
	for(const auto &c:t){
		cout<<c<<'\t';
	}
	cout<<endl;
}
#endif

