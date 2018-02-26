#include<iostream>
#include<string>
using namespace std;
class cp{
	public:
		cp(string s){
			cout<<"init func:"<<s<<endl;

		}
		cp(const cp &p){
			cout<<"copy func"<<endl;
		}

};
int main(){
	cp a("123");	
	cp b = a;
	string d = "abc";
	cp c = d;
	cp e = b;
	cout<<"==0=="<<endl;
	b = c;
	c = a;
	cout<<"==1=="<<endl;
	cp *p = new cp(a);
	cout<<"==2=="<<endl;
	cp *qas = new cp("xyuh");
	*p = b;

	return 0;
}
