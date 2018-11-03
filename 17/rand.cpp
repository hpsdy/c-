#include<random>
#include<cstdio>
#include<getopt.h>
#include<sstream>
int main(int argc,char *argv[]){
	opterr = 0;
	char arg;
	char randint[32] = {'\0'};
	while ((arg = getopt(argc, argv, ":i:")) != -1){
		switch(arg){
			case 'i':
				snprintf(randint, sizeof(randint), "%s" , optarg);
				break;
			case '?':
				printf("无法识别\n");
				break;
			case ':':
				printf("丢失参数\n");
				break;
			default:
				printf("default\n");
				break;
		}
	}
	unsigned int randnum = 0;
	std::stringstream str;
	str<<randint;
	str>>randnum;
	printf("arg:%d\n",randnum);
	std::default_random_engine e(randnum);
	std::uniform_int_distribution<unsigned> u(0,9);
	for (int i = 0; i<20; ++i){
		printf("%ld\t", u(e));		
	}
	printf("\n");
	return 0;
	
}
