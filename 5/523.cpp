//#include<exception>
#include<stdexcept>
#include"head.h"

int main(){

	int x,y;
	while(true){
		try{
			string qin="qinhan";
			cout<<qin<<endl;
			cin>>x>>y;
			cout<<x/y<<endl;
			//throw runtime_error("some error");
			throw exception();
		}catch(exception e){
		//}catch(runtime_error e){
			cout<<"xxyy:"<<e.what()<<" "<<typeid(e).name()<<endl;
			cout<<"continue?Y/N:"<<endl;
			char p;
			cin>>p;
			char w = tolower(p);
			cout<<"p:"<<p<<",w:"<<w<<endl;
			if(w=='y'){
				continue;
			}else{
				break;
			}
							
		}
	}
	return 0;
}
