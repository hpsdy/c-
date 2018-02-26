#include"head.h"
void sort_unique(vector<string> &strs){
	sort(strs.begin(),strs.end());
	auto de = unique(strs.begin(),strs.end());
	for(auto & c:strs){
		cout<<c<<'\t';
	}
	cout<<endl;
	strs.erase(de,strs.end());
	for(auto &c:strs){
		cout<<c<<'\t';
	}
	cout<<endl;

}
int main(){
	fstream fn("book.txt",fstream::in|fstream::out);
	if(fn){
		vector<string> strs;
		string str;
		while(fn>>str){
			strs.push_back(str);
		}
		sort_unique(strs);		
	}else{
		cout<<"打开文件失败"<<endl;
	}	
	fn.close();
	return 0;
}
