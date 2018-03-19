#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Foo {
  public:
    Foo() {
        cout << "默认构造函数:" << this << endl;
    };
    Foo(const Foo &f) {
        cout << "拷贝构造函数:" << this << endl;
        data = f.data;
    }
    Foo(Foo &&f) {
        cout << "移动构造函数:" << this << endl;
        data = std::move(f.data);
    }
    Foo sorted() &&;
    Foo sorted() const &;
    ~Foo() {
        cout << "析构函数:" << this << endl;
        data.clear();
    }
    void print() {
        cout << "print:" << this << endl;
        for (auto &c : data) {
            cout << c << endl;
        }
    }
  private:
    vector<int> data;

};
Foo Foo::sorted() && {
    cout << "右值引用版本:" << this << endl;
    sort(data.begin(), data.end());
    return *this;
}
Foo Foo::sorted() const & {
    cout << "左值引用版本:" << this << endl;
    //Foo ret(*this);
    //return ret.sorted();
    return Foo(*this).sorted();

}
int main(int argc, char const *argv[]) {
    Foo f;
    Foo c = f.sorted();
    c.print();
    return 0;
}