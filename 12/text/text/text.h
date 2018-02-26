#ifndef TEXT
#define TEXT
#include<memory>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<fstream>
#include<sstream>
#include"result.h"
using namespace std;
typedef vector<string>::size_type line;
typedef shared_ptr<vector<string>> fvec;
typedef map<string,shared_ptr<set<line>>> kmap;
class result;
class text{
	public:
		text(ifstream &);
		result query(string str);
	private:
		fvec file;
		kmap keymap;	
};
#endif
