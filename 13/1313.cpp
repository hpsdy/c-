#include<iostream>
#include<string>
#include<gflags/gflags.h>
using namespace std;
class strC{
	public:
		strC(string str):str(str){cout<<"strC construct:"<<str<<endl;}
		~strC(){cout<<"strC destory"<<endl;}
	private:
		string str;
};
#define funcFactory(basename) \
class basename##Factory{ \
	public: \
		basename##Factory(string str):str(new strC(str)){cout<<"base construct:" \
<<endl;} \
		~basename##Factory(){ \
			cout<<"base des"<<endl; \
		} \
	private: \
		strC *str; \
};
using namespace std;
DEFINE_string(str,"ooxx","xxoo");
int main(int argc,char **argv){
	gflags::ParseCommandLineFlags(&argc,&argv,true);
	funcFactory(base)
	baseFactory a(FLAGS_str);	
	return 0;
}

