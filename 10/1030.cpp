#include"head.h"
#include<iterator>
int main(){
	istream_iterator<int> in(cin);
	istream_iterator<int> ep;
	ostream_iterator<int> out(cout,"\t");
	vector<int> vc(in,ep);
	sort(vc.begin(),vc.end());
	vector<int> ret;
	auto xret = back_inserter(ret);
	unique_copy(vc.begin(),vc.end(),xret);
	copy(ret.begin(),ret.end(),out);
	return 0;
}
