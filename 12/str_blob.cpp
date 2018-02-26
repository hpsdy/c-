#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<stdexcept>
#include<initializer_list>
using namespace std;
typedef shared_ptr<vector<string>> sp;
typedef weak_ptr<vector<string>> wp;
class strBlobPtr;
class strBlob{
	friend class strBlobPtr;
	public:
	strBlob():data(new vector<string>()){};
	strBlob(initializer_list<string> pl) :data(make_shared<vector<string>>(pl)){};
	string cur(size_t size){
		check(size);
		return data->at(size);
	}
	inline strBlobPtr begin();
	inline strBlobPtr end();
	private:
	sp data;
	void check(size_t size){
		if(size>=data->size()){
			throw out_of_range("超出索引");
		}	
	}

};
class strBlobPtr{
	public:
	strBlobPtr(){};
	strBlobPtr(const strBlob &p):data(p.data){};
	strBlobPtr(const strBlob &p,size_t size):data(p.data),cur(size){};
	string ref(){
		auto ret = check(cur);
		return ret->at(cur);
	}
	strBlobPtr & incre(){
		check(cur);
		++cur;
		return *this;
	}
	bool operator!=(const strBlobPtr &p){
		return !(p.cur==cur);
	}
	private:
	size_t cur=0;
	wp data;	
	sp check(size_t size){
		sp tmp = data.lock();
		if(!tmp){
			throw runtime_error("对象内存已释放");
		}
		if(size>=tmp->size()){
			throw out_of_range("超出范围");
		}
		return tmp;
	}

};
inline strBlobPtr strBlob::begin(){
	return strBlobPtr(*this);
}	
inline strBlobPtr strBlob::end(){
	return strBlobPtr(*this,data->size());
}

int main(){
        strBlob one({"abc","cde","efj"});
	for(auto b = one.begin();b!=one.end();b.incre()){
		cout<<b.ref()<<endl;
	}	
	return 0;
}
