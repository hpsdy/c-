#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Foo {
  public:
    Foo() {
        cout << "默认构造函数" << endl;
    };
    Foo(const Foo &f) {
        cout << "拷贝构造函数" << endl;
        data = f.data;
    }
    Foo(Foo &&f) {
        cout << "移动构造函数" << endl;
        data = std::move(f.data);
    }
    Foo sorted() &&;
    Foo sorted() const &;
    ~Foo() = default;
  private:
    vector<int> data;

};
Foo Foo::sorted() && {
    cout << "右值引用版本" << endl;
    sort(data.begin(), data.end());
    return *this;
}
Foo Foo::sorted() const & {
    cout << "左值引用版本" << endl;
    Foo ret(*this);
    return ret.sorted();
    //return Foo(*this).sorted();

}
int main(int argc, char const *argv[]) {
    Foo f;
    f.sorted();
    return 0;
}