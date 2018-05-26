#include "basket.cpp"
#include <iostream>
using namespace std;
int main(){
	basket arr;
	quote one("qin",100);
	bulk_quote two("han",50,8,0.2);
	bulk_quote thr("han",80,8,0.3);
	arr.add_item(one);
	arr.add_item(std::move(two));
	arr.add_item(one);
	arr.add_item(std::move(two));
	arr.add_item(std::move(thr));
	arr.total_receipt(cout);
	return 0;
}
