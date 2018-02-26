#include"head.h"
#include<algorithm>
#include<numeric>
int main(){
	int nums[] = {1,2,3,4,5,6,7,8,9};
	int sum = accumulate(begin(nums),end(nums),10);
	vector<string> strs = {"abc","def"};
	string str = accumulate(strs.begin(),strs.end(),string(""));
	cout<<sum<<endl;
	cout<<str<<endl;
	string x="abc";
	char y[] = "abc";
	if(x==y){
		cout<<"=="<<endl;
	}
	return 0;

}
