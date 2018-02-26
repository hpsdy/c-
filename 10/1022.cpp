#include"head.h"
#include<functional>
using namespace std::placeholders;
bool ltsize(const string &str,size_t size,istream & in){
	return str.size()<size;
}
int main(){
	fstream fs("num.txt",fstream::in);
	vector<int> nums;
	if(fs){
		int num;
		while(fs>>num){
			nums.push_back(num);
		}
		fs.close();
	}
	string str;
	getline(cin,str);
	auto size = str.size();
	auto p = find_if(nums.begin(),nums.end(),bind(ltsize,ref(str),_1,ref(cin)));
	if(p==nums.end()){
		cout<<"nofind"<<endl;
	}else{
		cout<<*p<<endl;
	}
	return 0;				 
}
