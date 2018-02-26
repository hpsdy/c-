#ifndef RESULT
#define RESULT
#include<memory>
#include<string>
#include<vector>
#include<set>
#include<fstream>
using namespace std;
class result{
	friend void print(ostream &,result &);
	public:
		typedef vector<string>::size_type line;
		typedef shared_ptr<set<line>> lset;
		typedef shared_ptr<vector<string>> fvec;
		result(string k,lset l,fvec f):key(k),lines(l),file(f){}
	private:
		string key;
		lset lines;
		fvec file;
				
};
#endif
