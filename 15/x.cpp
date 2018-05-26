#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

int main(){
	char x[9] = {'\0'};
	snprintf(x,sizeof(x),"%08x",100);
	cout<<x<<endl;
	int a=100;
	cout<<(a>>2)<<endl;
	cout<<a<<endl;
	stringstream str(x);
	int num;
	str>>num;
	cout<<num<<endl;
	cout<<x<<endl;
	sscanf(x,"*%d",num);
	cout<<"x:"<<num<<endl;
	cout<<x<<endl;
	int arr[10] = {0};
	char w = '\0';
	char z = 0;
	if(w==z){
		cout<<"==="<<endl;
	}
	cout<<arr<<endl;
	typedef struct _t_s{
		char * a[10];
		int num;
	} ts;
	ts *ab = NULL;
	if(ab->a==NULL){
		cout<<"null_111"<<endl;
	}

	if(NULL==nullptr){
		cout<<"asdsadsada"<<endl;
	}
	const char *xxx = "asdas";
	cout<<"size:"<<sizeof(ts)<<endl;
	ab = new ts;
	memset(ab,0,sizeof(ts));
	cout<<&(ab->a)<<endl;
	cout<<"size:"<<sizeof(ts)<<endl;
	if(ab->a==NULL){
		cout<<"null_222"<<endl;
	}
	cout<<"end"<<endl;
	return 0;

}
