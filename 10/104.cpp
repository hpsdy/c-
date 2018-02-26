#include"head.h"
#include<algorithm>
#include<numeric>
#include<fstream>
int main(){
	vector<long double> arr;
	fstream fn("num.txt",fstream::binary|fstream::in|fstream::ate);
	if(fn){
		auto size=fn.tellg();
		cout<<size<<endl;
		char *p = new char[size];
		fn.seekg(0,fstream::beg);
		fn.read(p,size);
		cout<<"qinhan:"<<p<<endl;
		string str;
		fn.seekg(0,fstream::beg);
		getline(fn,str);
		cout<<str<<endl;
		cout<<"fn"<<endl;
		cout<<fn.tellg()<<endl;
		cout<<fn.seekg(0)<<endl;
		long double num;
		while(fn>>num){
			cout<<num<<'\t';
			arr.push_back(num);	
		}		
	}
	fn.close();
	for(auto &c:arr){
		cout<<c<<endl;
	}
	auto sum = accumulate(arr.begin(),arr.end(),0);
	cout<<typeid(sum).name()<<":"<<sum<<endl;
	return 0;
	
}
