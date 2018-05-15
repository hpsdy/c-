#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class basket;
class quote {
  public:
    friend class basket;
   // quote() = default;
    virtual quote* clone() const &{
	return new quote(*this);
    }
    virtual quote* clone() &&{
	return new quote(std::move(*this));
    }

    virtual ~quote() {}
    quote(string name, double price): bno(name), price(price) {}
    string bookNo() const;
    virtual double net_price(int size) const;
  private:
    string bno;
  protected:
    double price = 0.0;
};
string quote::bookNo() const {
    stringstream ss;
    ss<<price;
    return bno+":"+ss.str();
}
double quote::net_price(int size) const{
    return size * price;
}
double print_total(ostream &io, const quote &obj, int size) {
    double ret = obj.net_price(size);
    io << obj.bookNo() << ":" << ret << "/" << size << endl;
    return ret;
}
