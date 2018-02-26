#include<iostream>
#include<string>
#include<cctype>
using namespace std;
int main(){
	char in;
	cin>>in;
	cout<<"in:"<<in<<endl;
	if(isalnum(in)){
		cout<<"in数字或字母:"<<in<<endl;
	}
	if(isalpha(in)){
		cout<<"in字母:"<<in<<endl;
	}
	if(iscntrl(in)){
		cout<<"in控制字符:"<<in<<endl;
	}
	if(isdigit(in)){
		cout<<"in数字:"<<in<<endl;
	}
	if(isgraph(in)){
		cout<<"in非空格可打印:"<<in<<endl;
	}
	if(islower(in)){
		cout<<"in小写字母:"<<in<<endl;
	}
	if(isprint(in)){
		cout<<"in可打印:"<<in<<endl;
	}
	if(ispunct(in)){
		cout<<"in标点符号:"<<in<<endl;
	}
	if(isspace(in)){
		cout<<"in空白符:"<<in<<endl;
	}
	if(isupper(in)){
		cout<<"in大写字母:"<<in<<endl;
	}
	if(isxdigit(in)){
		cout<<"in16进制:"<<in<<endl;
	}
	cout<<"in转大写:"<<toupper(in)<<endl;
	cout<<"in转小写:"<<tolower(in)<<endl;




	return 0;
}
