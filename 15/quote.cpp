#include <iostream>
#include <string>
using namespace std;
class quote {
  public:
    quote() = default;
    virtual ~quote() {}
    quote(string name, double price): bno(name), price(price) {}
    string bookNo() const;
    virtual double net_price(int size);
  private:
    string bno;
  protected:
    double price = 0.0;
};
string quote::bookNo() const {
    return bno;
}
double quote::net_price(int size) {
    return size * price;
}
double print_total(ostream &io, const quote &obj, int size) {
    double ret = obj.net_price(size);
    io << obj.bookNo << ":" << ret << "/" << size << endl;
    return ret;
}