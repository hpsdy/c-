#include<random>
#include<iostream>
#include<ctime>
using namespace std;
int main(){
	random_device rd;
	cout<<rd.min()<<":"<<rd.max()<<endl;
	cout<<rd()<<endl;
	cout<<rd()<<endl;
	cout<<rd.entropy()<<endl;
	cout<<time(0)<<endl;
	srand(time(0));
	cout<<rand()<<endl;
	cout<<rand()<<endl;
	cout<<rand()<<endl;
	cout<<rand()<<endl;

	return 0;

}
