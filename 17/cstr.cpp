#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<bitset>
using namespace std;
string string_to_hex(const string& str) //transfer string to hex-string
{
    string result="";
    string tmp;
    stringstream ss;
    ss<<hex;
    for(int i=0;i<str.size();i++)
    {
	ss.clear();
	ss.str("");
	unsigned char t(str[i]);
	unsigned int x(t);
        ss<<x;
        ss>>tmp;
        result+=tmp;
    }
    return result;
}
int main(){
	int ab = 123;
	int &ba = ab;
	cout<<&ab<<endl;
	cout<<&ba<<endl;
	char xx[100] = {'\0'};
	int ret = snprintf(xx, 3, "%s", "abcde");
	cout<<ret<<endl;
	cout<<xx<<endl;
	cout<<strlen(xx)<<endl;
	cout<<sizeof(xx)<<endl;
	char *b = xx;
	
	string a = "秦瀚";
	cout<<"size:"<<a.size()<<endl;
	string x = string_to_hex(a);
	cout<<x<<endl;
	return 0;

}
