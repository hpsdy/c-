#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main(){
	vector<unsigned int> scores(11);
	auto ite = scores.begin();
	unsigned int score;
	while(cin>>score){
		if(score<101){
			++*(ite+(score/10));		
		}else{
			cout<<score<<"is more"<<endl;
		}
	}
	for(auto num:scores){
		cout<<num<<"\t";
	}
	cout<<endl;
	return 0;
}
