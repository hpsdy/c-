#ifndef STRVEC
#define STRVEC
#include<memory>
#include<utility>
#include<string>
#include "string.h"
using namespace user;
class strVec{
	public:
		strVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
		strVec(const strVec &);
		strVec & operator=(const strVec &); 
		~strVec(){
			free();
		}
		std::size_t size(){
			return first_free-elements;
		}
		std::size_t capacity(){
			return cap-elements;
		}
		void push_back(const std::string &);
		std::string *begin() const{ return elements;}
		std::string *end() const{ return first_free;}
	private:
		static std::allocator<std::string> alloc;
		std::string *elements;
		std::string *first_free;
		std::string *cap;
		void check_n_alloc(){
			if(size()==capacity()){
				reallocate();
			}
		}	
		void reallocate();
		void free();
		std::pair<std::string *,std::string *> alloc_n_copy(const std::string *,const std::string *);
};
class StrVec{
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
		StrVec(const StrVec &);
		StrVec & operator=(const StrVec &); 
		~StrVec(){
			free();
		}
		std::size_t size(){
			return first_free-elements;
		}
		std::size_t capacity(){
			return cap-elements;
		}
		void push_back(const String &);
		String *begin() const{ return elements;}
		String *end() const{ return first_free;}
	private:
		static std::allocator<String> alloc;
		String *elements;
		String *first_free;
		String *cap;
		void check_n_alloc(){
			if(size()==capacity()){
				reallocate();
			}
		}	
		void reallocate();
		void free();
		std::pair<String *,String *> alloc_n_copy(const String *,const String *);
};
//std::allocator<std::string> strVec::alloc;
//std::allocator<String> StrVec::alloc;
#endif
