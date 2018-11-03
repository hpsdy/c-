#include<regex>
#include<cstdio>
#include<string>
#include<iostream>
int main(){
	bool x = -20;
	printf("bool:%d\n",x);
	std::string pattern = "([[:alpha:]]+)?(ie|ci)([[:alpha:]]+)?";
	std::regex r(pattern,std::regex::icase);
	std::string str;
	//std::cin>>str;
	getline(std::cin,str);
	std::smatch results;
	try{
		if (std::regex_search(str,results,r)){
			for (std::sregex_iterator it(str.begin(),str.end(),r),end_it; it!=end_it; ++it){
				printf("result:%s\n",it->str().c_str());
				printf("prefix:%s\n",it->prefix().str().c_str());
				printf("suffix:%s\n",it->suffix().str().c_str());
				printf("ready:%d\n",it->ready());
				printf("size:%d\n",it->size());
				printf("=====sub=====\n");
				for (int i=0; i<it->size(); ++i){				
					printf("sub_len_%d:%d\n",i,it->length(i));
					printf("sub_position_%d:%d\n",i,it->position(i));
					printf("sub_str_%d:%s\n",i,it->str(i).c_str());
					printf("sub_match_%d:%s\n",i,(*it)[i].str().c_str());
				}
				printf("=====endsub=====\n");
				printf("=====ssub_match=====\n");
				for (auto b = it->begin(),e = it->end();b!=e;++b){
					printf("length:%d,str:%s,match:%d\n",b->length(),b->str().c_str(),b->matched);
				}
				printf("=====endssub_match=====\n");
				printf("=====end=====\n");
			}
		}else{
			printf("no match\n");
		}
	}catch(std::regex_error e){
		printf("code:%d,msg:%s\n",e.code(),e.what());
	}catch(...){
		printf("some exp\n");
	}
	return 0;
	

}
