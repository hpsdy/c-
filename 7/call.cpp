#include"head.h"
class Nodefault{
	public:
	Nodefault(){
		cout<<"Nodefault n:"<<n<<endl;
	};
	Nodefault(string str){
		cout<<str<<endl;
	}
	private:
	int n;
};
class one{
	public:
	//one(string str=""):sd(str){
	one(){
		cout<<"default init:"<<num<<endl;
	}
	private:
	Nodefault sd;
	int num;
};


int main(){
	one *a = new one;
	one *b = new one();
	one c;
	return 0;
}
