#include"head.h"
void print(string str,bool isnum=0){
	string::size_type p = 0;
	string filter;
	if(isnum){
		filter = "0123456789";
	}else{
		filter = "abcdefghijkmlnopqrstuvwxyz";
	}
		while((p=str.find_first_of(filter,p))!=string::npos){
			cout<<str[p];
			++p;
		}
		cout<<endl;
	return ;
}
int main(){
	string str;
	getline(cin,str);
	cout<<str<<endl;
	print(str);
	print(str,1);
	str.push_back("a");
	cout<<str<<endl;
	str.append("abc");
	cout<<str<<endl;
	return 0;

}
