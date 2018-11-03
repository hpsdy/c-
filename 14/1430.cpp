#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
using namespace std;
struct point {
    friend std::istream &operator>>(std::istream &io, point &p) {
        std::string str;
        istream &tmp = getline(io, str);
        std::cout << "io status:" << tmp.good() << std::endl;
        p.data.push_back(str);
        return io;

    }
    friend std::ostream &operator<<(std::ostream &io, const point &p) {
        for (const auto &c : p.data) {
            io << c << std::endl;
        }
        return io;

    }
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
        std::cout << size << ":" << data.size() << ":" << cur << std::endl;
        bool ret = check(pcur);
        if (ret) {
            cur = pcur;
        }
    }
    const std::string &operator()(bool is, const string &p1, const string &p2) {
        return is ? p1 : p2;
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

std::istream &operator>>(std::istream &io, point &p);
std::ostream &operator<<(std::ostream &io, const point &p);

class intCompare {
  public:
    intCompare(int num): initNum(num) {}
    bool operator()(int num) {
        return num == initNum;
    }
  private:
    int initNum;
};

int main(int argc, char const *argv[]) {
    point p({"qinhan", "han"});
    try {
        std::cout << *p << std::endl;
        *p = "world";
        std::cout << *p << std::endl;
        std::cout << p->size() << std::endl;
        p.setCur(1);
        p.setCur(1);
        std::cout << p->size() << std::endl;
        std::cout << *p << std::endl;
        p.setCur(2);
        std::cout << p(true, "xxxooo", "oooxxx") << std::endl;
        std::cout << p(false, "xxxooo", "oooxxx") << std::endl;
    } catch (std::runtime_error ext) {
        std::cout << "ext:" << ext.what() << std::endl;
    }
    std::cin >> p;
    std::cout << p;
    std::vector<int> numarr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    for (auto &c : numarr) {
        std::cout << c << std::endl;
    }
    replace_if(numarr.begin(), numarr.end(), intCompare(6), 100);
    for (auto &c : numarr) {
        std::cout << c << std::endl;
    }
    std::cout << "========" << std::endl;
    int a = 10;
    auto f = [&a] {return ++a;};
    std::cout << f() << std::endl;
    std::cout << a << std::endl;
    return 0;
}
