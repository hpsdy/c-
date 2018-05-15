#include<iostream>
#include<string>
class oper{
	public:
		operator int(){
			std::cout<<"operator int"<<std::endl;
			return num;
		}
		operator float(){
			std::cout<<"operator int"<<std::endl;
			return num;
		}

		explicit operator std::string(){
			std::cout<<"operator string"<<std::endl;
			return "qinhan";
		}
	private:
		float num = 999.9f;

};
int main(){
	oper one;
	std::cout<<one+100.9f<<std::endl;
	std::string str = static_cast<std::string>(one);
	std::cout<<str<<std::endl;
	return 0;
}
