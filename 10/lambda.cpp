#include"head.h"
int base = 99;
void sort_filter(vector<string> strs,size_t sizes){
	sort(strs.begin(),strs.end());
	auto ep = unique(strs.begin(),strs.end());
	auto dp = strs.erase(ep,strs.end());
	auto mid = stable_partition(strs.begin(),strs.end(),[sizes](const string &str){return str.size()>=sizes;});
	for_each(strs.begin(),mid,[](const string &str){cout<<str<<'\t';});
	cout<<endl;
}
int main(){
	int (*f)(const int &,const int &) = [](const int &a,const int &b)->int{return a+b;};
	cout<<typeid(f).name()<<endl;
	cout<<f(10,99)<<endl;
	int num;
	cin>>num;
	auto myand = [num](int n){return num+n+base;};
	cout<<myand(10)<<endl;
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
		sort_filter(strs,4);
                cout<<endl;
        }
        cout<<"===================="<<endl;
	int sn = 10;
	auto ra = [sn]()mutable{return ++sn;};
	cout<<sn<<endl;
	cout<<ra()<<endl;
	cout<<sn<<endl;
	sn = 0;
	cout<<ra()<<endl;
	cout<<sn<<endl;
        cout<<"===================="<<endl;
	sn = 10;
	auto xa = [&sn](){return ++sn;};
	cout<<sn<<endl;
	cout<<xa()<<endl;
	cout<<sn<<endl;
	sn = 0;
	cout<<xa()<<endl;
	cout<<sn<<endl;

	return 0;

}
