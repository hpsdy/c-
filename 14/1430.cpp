#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
using namespace std;
struct point {
  public:
    point(std::initializer_list<string> strList): data(strList), size(data.size()) {
        std::cout << "构造函数" << std::endl;
    }
    string &operator*() {
        bool ret = check(cur);
        return data[cur];
    }
    string *operator->() {
        return &this->operator*();
    }
    void setCur(std::size_t pcur) {
        bool ret = check(cur);
        if (ret) {
            cur = pcur;
        }
    }
  private:
    std::vector<string> data;
    std::size_t size;
    std::size_t cur = 0;
    bool check(int cur) {
        if (cur >= size) {
            std::cout << "内存溢出" << std::endl;
            throw std::runtime_error("内存溢出");
            return false;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    try {
        point p{"qinhan", "han"};
        std::cout << *p << std::endl;
        *p = "world";
        std::cout << *p << std::endl;
        std::cout << p->size() << std::endl;
        p.setCur(1);
        std::cout << p->size() << std::endl;
        std::cout << *p << std::endl;
    } catch (std::runtime_error ext) {
        std::cout << "ext:" << ext.what() << std::endl;
    }
    return 0;
}