#include"sale_data.h"
int main(){
	sale_data sale_info;
	if(read(cin,sale_info)){
		sale_data tmp;
		//cout<<"bookNo:"<<sale_info.bookNo<<endl;
		while(read(cin,tmp)){
			if(tmp.isbn()==sale_info.isbn()){
				sale_info.combine(tmp);
			}else{
				print(cout,sale_info)<<endl;
				sale_info=tmp;
			}
		}
		print(cout,sale_info)<<endl;
	}else{
		cout<<"no data"<<endl;
	}
	return 0;
}
