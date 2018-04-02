#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
void input(std::istream &io, std::vector<std::string> &vec) {
    std::string str;
    while (io >> str) {
        vec.push_back(str);
    }
}
int main(int argc, char const *argv[]) {
    std::vector<std::string> vec;
    input(std::cin, vec);
    int num = std::count_if(vec.cbegin(), vec.cend(), std::bind(std::equal_to<std::string>(), std::placeholders::_1, "qin"));
    std::cout << num << std::endl;
    auto fir = std::find_if(vec.cbegin(), vec.cend(), std::bind(std::not_equal_to<std::string>(), std::placeholders::_1, "han"));
    std::cout << *fir << std::endl;
    std::for_each(vec.begin(), vec.end(), std::bind(std::plus<std::string>(), "pref", std::placeholders::_1));
    std::cout << "========" << std::endl;
    for (auto &c : vec) {
        std::cout << c << std::endl;
    }
    std::vector<int> intarr{2, 4, 6, 8, 10};
    num = std::count_if(intarr.cbegin(), intarr.cend(), std::bind(std::modulus<int>(), 10, std::placeholders::_1));
    std::cout << num << std::endl;
 
    return 0;
}