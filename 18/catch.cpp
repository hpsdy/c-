#include<exception>
#include<stdexcept>
#include<cstdio>
class test{
	public:
	test(){
		printf("test\n");
	}
	virtual void t1(){
		printf("t1\n");
	}
	void t2(){
		printf("t2\n");
	}
	void t3(){
		printf("t3\n");
	}

};
class son:public test{
	public:
	son(){
		printf("son\n");
	}
	void t1(){
		printf("sont1\n");
	}
	void t2(){
		printf("sont2\n");
	}
	void t4(){
		printf("sont4\n");
	}

};
int main(){
	son a = son();
	test b = a;
	a.t1();
	a.t2();
	a.t3();
	a.t4();
	b.t1();
	b.t2();
	b.t3();
	//b.t4();
	test *c = &a;
	c->t1();
	c->t2();
	c->t3();
	//c->t4();
	try{
		try{
//			throw *c;
			throw int(10);
		}catch(int a){
			printf("exp1:%d\n",a);
		//	throw double(1000.01);
//			throw;
		}catch(double d){
			printf("exp2:%lf\n",d);
		}
		printf("inline excp\n");
	}catch(double d){
		printf("exp3:%lf\n",d);
	}catch(int a){
		printf("exp4:%d\n",a);
		
	}catch(test &c){
		printf("test excp\n");
		c.t1();
	}catch(...){
		printf("final exp\n");
	}
	printf("end excp\n");
	return 0;
	

}
