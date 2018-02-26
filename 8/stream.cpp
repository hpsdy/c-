#include"head.h"


int main(){
	int a=10;
	cout<<(a>>2)<<endl;
	cout<<"state:"<<cin.rdstate()<<endl;
	cout<<"good:"<<cin.goodbit<<" "<<~cin.goodbit<<endl;
	cout<<"bad:"<<cin.badbit<<" "<<~cin.badbit<<endl;
	cout<<"eof:"<<cin.eofbit<<" "<<~cin.eofbit<<endl;
	cout<<"fail:"<<cin.failbit<<" "<<~cin.failbit<<endl;

	cout<<"+++++++++++++++++++++++"<<endl;
	auto state = cin.rdstate();
	auto ori = state;
	int num;
		cin>>num;
		state = cin.rdstate();
		auto oldstate = state;
		cout<<"state:"<<state<<endl;
		cin.clear();	
		state = cin.rdstate();
		cout<<"state:"<<state<<endl;
		cin.setstate(ori);
		state = cin.rdstate();
		cout<<"ori state:"<<ori<<" "<<state<<endl;
	cout<<"+++++++++++++++++++++++"<<endl;
		cin.clear();	
		cin.setstate(cin.badbit);
		cin.setstate(cin.failbit);
		cin.setstate(cin.eofbit);
		if(cin.bad()){
			cout<<"bad"<<endl;
			state = cin.rdstate();
			cout<<"state:"<<state<<endl;
			//cin.clear(state & ~cin.badbit & ~cin.failbit & ~cin.eofbit);	
			cin.clear(state & ~cin.badbit & ~cin.failbit & ~cin.eofbit);	
			//cin.clear();	
			state = cin.rdstate();
			cout<<"state:"<<state<<endl;
		}		
	cout<<"+++++++++++++++++++++++"<<endl;
		cin.clear();	
		cin.setstate(cin.failbit);
		if(cin.fail()){
			cout<<"fail"<<endl;
			state = cin.rdstate();
			cout<<"state:"<<state<<endl;
			cin.clear(~cin.failbit);	
			state = cin.rdstate();
			cout<<"state:"<<state<<endl;
		}
	cout<<"+++++++++++++++++++++++"<<endl;
		cin.clear();	
		cin.setstate(cin.eofbit);
		if(cin.eof()){
			cout<<"eof"<<endl;
			state = cin.rdstate();
			cout<<"state:"<<state<<endl;
			cin.clear(cin.eofbit);	
			state = cin.rdstate();
			cout<<"state:"<<state<<endl;
		}
	return 0;
}
