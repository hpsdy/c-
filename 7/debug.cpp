#include"head.h"
/*
 *字面值常量类constexpr
 */
class debug{
	public:
	constexpr debug(bool io,bool other):io(io),other(other){}
	private:
	bool io,other;
};
int main(){
	constexpr debug one(1,1);
	return 0;
}
