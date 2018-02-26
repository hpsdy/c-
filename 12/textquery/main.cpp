#include"head.h"
#include"textresult.cpp"
#include"textquery.cpp"
int main(){
	textquery tree("textquery.cpp");
	while(true){
		cout<<"please input key or q:"<<endl;
		string tmp;
		if(!(cin>>tmp) || tmp=="q"){
			break;
		}
		auto result = tree.query(tmp);
		cout<<"=============="<<endl;
		cout<<result.key<<endl;
		for(auto &c:result.scores){
			cout<<c<<'\t';
		}	
		cout<<endl;
		for(auto &c:result.lines){
			cout<<c<<endl;	
		}
		cout<<"=============="<<endl;
	}
	return 0;
}
