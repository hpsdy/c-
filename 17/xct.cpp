#include<cstdio>
class t{
	public:
	t(int a){
		printf("t:%d\n",a);
	}
	protected:
	~t(){
		printf("t:des\n");
	}
};
class t1:public t{
	using t::t;
};



int main(){
	t1 *a = new t1(10);
	delete a;
	return 0;

}
