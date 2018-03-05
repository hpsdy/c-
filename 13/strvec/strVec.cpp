#include"strVec.h"
#include<string>
void strVec::push_back(const std::string &str){
	check_n_alloc();
	alloc.construct(first_free++,str);
}
std::pair<std::string*,std::string*> strVec::alloc_n_copy(const std::string *b,const std::string *e){
	std::string * p = alloc.allocate(e-b);
	return {p,std::uninitialized_copy(b,e,p)};
}
void strVec::free(){
	if(!elements){
		return;
	}
	while(elements!=first_free){
		alloc.destroy(--first_free);
	}
	alloc.deallocate(elements,capacity());
}
strVec::strVec(const strVec &p){
	auto data = alloc_n_copy(p.begin(),p.end());
	elements = data.first;
	first_free = cap = data.second;
}
strVec & strVec::operator=(const strVec &p){
	auto data = alloc_n_copy(p.begin(),p.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
void strVec::reallocate(){
	std::size_t newCapCity = size()?2*size():1;
	std::string *p = alloc.allocate(newCapCity);
	auto dest = p;
	auto elem = elements;
	for(std::size_t i=0,num=size();i<num;++i){
		alloc.construct(dest++,std::move(*elem++));
	}
	free();
	elements = p;
	first_free = dest;
	cap = p+newCapCity;
	
}



void StrVec::push_back(const String &str){
	check_n_alloc();
	alloc.construct(first_free++,str);
}
std::pair<String*,String*> StrVec::alloc_n_copy(const String *b,const String *e){
	String * p = alloc.allocate(e-b);
	return {p,std::uninitialized_copy(b,e,p)};
}
void StrVec::free(){
	if(!elements){
		return;
	}
	while(elements!=first_free){
		alloc.destroy(--first_free);
	}
	alloc.deallocate(elements,capacity());
}
StrVec::StrVec(const StrVec &p){
	auto data = alloc_n_copy(p.begin(),p.end());
	elements = data.first;
	first_free = cap = data.second;
}
StrVec & StrVec::operator=(const StrVec &p){
	auto data = alloc_n_copy(p.begin(),p.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
void StrVec::reallocate(){
	std::size_t newCapCity = size()?2*size():1;
	String *p = alloc.allocate(newCapCity);
	auto dest = p;
	auto elem = elements;
	for(std::size_t i=0,num=size();i<num;++i){
		alloc.construct(dest++,std::move(*elem++));
	}
	free();
	elements = p;
	first_free = dest;
	cap = p+newCapCity;
	
}