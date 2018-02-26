#include "head.h"
int main(){
	string tmp;
	vector<string> strArr;
	int num = 0;
	int mnum = 0;
	string pre = "",most = "";
	while(cin>>tmp){
		strArr.push_back(tmp);

		cout<<most<<":"<<mnum<<":"<<pre<<":"<<num<<":"<<tmp<<endl;
		if(tmp!=pre){
			num = 0;
			pre = tmp;
		}
		++num;
		if(num>mnum){
			most = pre;
			mnum = num;
		}

	}
	for (auto &c:strArr){
		cout<<c<<'\t';
	}
	cout<<endl;
	cout<<most<<":"<<mnum<<endl;
	return 0;
}
