#ifndef INCLUDE_GET_TOKEN_STR
#define INCLUDE_GET_TOKEN_STR
#include<cstring>
char *get_token_str(char *b,const char *dl){
	if(b==nullptr || dl==nullptr){
		return nullptr;
	}
	char *tb = b;
	char *te = strstr(b,dl);
	if(strlen(dl)>0 && te!=nullptr){
		*te = '\0';
		te += strlen(dl);
	}
	tb = te;
	return tb;

}
#endif
