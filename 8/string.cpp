#include"head.h"
#include<sstream>
#include<fstream>
class Person{
	public:
	string name;
	vector<string> phones;
};
int main(){
	string line,work;
	vector<Person> parr;
	stringstream record;
	fstream in("person.txt");
	while(getline(in,line)){
		Person tmp;
		record.clear();
		record.str(line);
		record>>tmp.name;
		while(record>>work){
			tmp.phones.push_back(work);		
		}
		parr.push_back(tmp);
	}
	ofstream out("person.txt",ofstream::app);
	for(const auto &c:parr){
		cout<<c.name<<'\t';
		out<<c.name<<'\t';
		for(const auto &ic:c.phones){
			cout<<ic<<'\t';
			out<<ic<<'\t';
		}
		cout<<endl;
		out<<'\n';

	}
	return 0;
}
