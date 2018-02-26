#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main(){
	string in;
	vector<string> txt;
	cout<<txt.empty()<<" "<<txt.size()<<endl;
	while(getline(cin,in)){
		txt.push_back(in);
	}
	for (auto it=txt.begin();it!=txt.end();++it){
		int i = 0;
		if (it->empty()){
			continue;
		}
		for (auto iit=it->begin();iit!=it->end();++iit){
			if(i==0 && isalpha(*iit)){
				*iit = toupper(*iit);
			} 	
			++i;
			if(isspace(*iit)){
				i = 0;
			}
		}
	}
	for (auto it:txt){
		cout<<it<<endl;
	}
	return 0;
}
