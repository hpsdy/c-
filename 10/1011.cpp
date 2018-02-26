#include"head.h"
bool islen=0;
bool mycompare(const string &p1,const string &p2){
	if(islen){
		return p1.size()<p2.size(); 
	}
	return p1<p2;
}
template<typename T>
void print(T arr){
	for(auto &c:arr){
		cout<<c<<'\t';
	}
	cout<<endl;
}
template<typename T>
void mysort(T arr){
	sort(arr.begin(),arr.end(),mycompare);
	print(arr);
	cout<<"========================="<<endl;
	auto copy = arr;
	islen=1;
	sort(arr.begin(),arr.end(),mycompare);	
	print(arr);
	cout<<"========================="<<endl;
	print(copy);
	cout<<"========================="<<endl;
	stable_sort(copy.begin(),copy.end(),mycompare);
	print(copy);
			
}
int main(){
	fstream fn("string.txt",fstream::in);
	if(fn){
		vector<string> arr;
		string str;
		while(fn>>str){
			arr.push_back(str);
		}	
		fn.close();
		mysort(arr);
	}
	return 0;	
}
