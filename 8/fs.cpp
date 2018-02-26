#include"head.h"
#include<fstream>

int main(int argc,char **argv){

	/*ofstream file("read.info");
	file.close();

	return 0;*/
	string str = argv[1];
	fstream fn(str);
	int i=0;
	string all;
	while(fn){
		++i;
		string content;
		getline(fn,content);
		all+=content+"\n";
		cout<<i<<":"<<content<<endl;
	}
	ofstream out("read.info",ofstream::app|ofstream::binary);
	out<<all;
	return 0;
}
