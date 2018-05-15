#include "bulk_quote.cpp"
#include <set>
#include <memory>
using namespace std;
class basket{
	public:
	void add_item(const quote &item){
		cout<<"step 1"<<endl;
	//	auto xxx = shared_ptr<quote>(new quote("xy",100));	
	//	items.insert(xxx);	
		items.insert(shared_ptr<quote>(item.clone()));	
	}
	void add_item(quote &&item){
		cout<<"step 2"<<endl;
		items.insert(shared_ptr<quote>(std::move(item).clone()));	
	}
	static bool compare(const shared_ptr<quote> &a,const shared_ptr<quote> &b){
		return (a->bno)<(b->bno);
	}
	double total_receipt(ostream &out){
		double sum = 0.0;
		for(auto iter = items.begin();iter != items.end();++iter){
			auto item = *iter;
			cout<<"item info:"<<(item->bookNo())<<endl;
		}	

		for(auto iter = items.begin();iter != items.end();iter = items.upper_bound(*iter)){
			sum += print_total(out,**iter,items.count(*iter));	
		}	
		cout<<"total_money:"<<sum<<endl;
		return sum;
	}
	private:
	multiset<shared_ptr<quote>,decltype(compare)*> items{compare};

};
