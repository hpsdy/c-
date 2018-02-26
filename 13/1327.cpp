#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class HasPtr{
	friend void swap(HasPtr & a,HasPtr & b){
		cout<<"class sawp"<<endl;
		using std::swap;
		swap(a.usei,b.usei);
		swap(a.s,b.s);
		swap(a.i,b.i);
	}
	friend void p(const HasPtr & a){
		cout<<*(a.s)<<endl;		
	}
	public:
		HasPtr(string str,int num):s(new string(str)),i(num),usei(new size_t(1)){
			cout<<*s<<":construct"<<endl;
		}
		HasPtr(const HasPtr &p):s(p.s),i(p.i),usei(p.usei){
			++(*usei);
			cout<<*s<<":copy construct"<<endl;
		}
		bool operator<(const HasPtr &a){
			cout<<*s<<":<"<<endl;
			return (*s)<=(*(a.s));
		}
		HasPtr & operator=(const HasPtr &p){
			++(*p.usei);
			if(--(*usei)==0){
				delete s;
				delete usei;
			}
			s = p.s;
			i = p.i;
			usei = p.usei;
			cout<<*s<<":operator="<<endl;
			return *this;
			
		}
		void f(){
			cout<<*s<<":f usei:"<<*usei<<endl;
		}
		~HasPtr(){
			cout<<*s<<":destory usei:"<<*usei<<endl;
			if(--(*usei)==0){
				delete s;
				delete usei;
			}
			cout<<"destory"<<endl;
		}
	private:
		string *s;
		int i;
		size_t *usei;
};

int main(){
	vector<HasPtr> arr;
	HasPtr a("abc",10);
	HasPtr b("dac",10);
	HasPtr c("ehs",10);
	HasPtr d("bas",10);
	arr.push_back(a);
	arr.push_back(b);
	arr.push_back(c);
	arr.push_back(d);
//	sort(arr.begin(),arr.end());
	for(auto &c:arr){
		p(c);
	}
	/*a.f();
	HasPtr b=a;
	b.f();
	HasPtr c=b;
	c.f();
	a=a;
	a.f();b.f();c.f();
	swap(a,b);*/
	return 0;
}
