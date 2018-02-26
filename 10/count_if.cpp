#include"head.h"
int main(){
	fstream fn("string.txt",fstream::in);
        if(fn){ 
                vector<string> strs;
                string str;
                while(fn>>str){
                        cout<<str<<'\t';
                        strs.push_back(str);
                }       
                cout<<"===================="<<endl;
                fn.close();
		int n=5;
		auto num=count_if(strs.begin(),strs.end(),[n](const string &str)->bool{return str.size()>=n;});
		cout<<num<<endl;
                cout<<endl;
        }
	int num=3;
	auto sm = [num]()mutable->bool{if(num>0){--num;return true;}else{return false;}};
	cout<<sm()<<endl;
	cout<<sm()<<endl;
	cout<<sm()<<endl;
	cout<<sm()<<endl;
	return 0;
}
