#include"folder.h"
#include<iostream>
#include<string>
using namespace std;
int main(){
	string name1 = "电影";
	string name2 = "游戏";
	string name1_1 = "西游记";
	string name1_2 = "终结者";
	string name2_1 = "DNF";
	string name2_2 = "绝地求生";
	msg c1_1(name1_1);
	msg c1_2(name1_2);
	msg c2_1(name2_1);
	msg c2_2(name2_2);
	
	folder f1(name1);
	folder f2(name2);
	
	return 0;
}
