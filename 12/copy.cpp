#include<iostream>
#include<string>
#include<memory>
#include<stdexcept>
using namespace std;
struct cn{
	cn(){
		cout<<"default construct"<<endl;
	};
	cn(string pstr){
		str = pstr;	
		cout<<"user construct"<<endl;
	}
	cn(cn &p){
		cout<<"copy construct"<<endl;
	}
	~cn(){
		cout<<"default destory:"<<str<<endl;
	}
	void pt(){
		cout<<str<<endl;
	}
	void operator=(const cn &p){
		cout<<"=="<<endl;
	}
	private:
	string str="default";
};
int main(){
	{
		cn obj;
		cout<<"===="<<endl;
		cn obj1(obj);
		cout<<"===="<<endl;
		cn obj2 = obj;
		cout<<"===="<<endl;
		obj1=obj2;
		cout<<"===="<<endl;
		cn o1("one1");
		cn o2("one2");
		cn o3("one3");
	}
	{
		cout<<"+++++++++++++++"<<endl;
		shared_ptr<cn> p(new cn);
		cout<<p.use_count()<<endl;
		shared_ptr<cn> q(p);
		cout<<q.use_count()<<endl;
		cn *obj = new cn("qinhan");
		p.reset(obj);
		cout<<q.use_count()<<endl;
		p->pt();
		p.reset();
		cout<<p<<endl;
	}
	{
		cout<<"+++++++++++++++"<<endl;
		unique_ptr<cn> up(new cn("unique"));
		cout<<up.get()<<endl;
		auto p = up.release();
		cout<<p<<endl;
		cout<<up.get()<<endl;
		
	}
	{
		cout<<"+++++++++++++++"<<endl;
		string *str = new string("中国人民万岁");
		try{
			throw runtime_error("some error");
			delete str;	
		}catch(runtime_error e){
			cout<<e.what()<<endl;
		}
		cout<<*str<<endl;

	}
	return 0;


}
