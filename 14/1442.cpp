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
    std::count_if(vec.cbegin(), vec.cend(), bind(std::equal_to<std::string>(), std::placeholders::_1, "qin"));
    auto fir = std::find_if(vec.cbegin(), vec.cend(), bind(std::not_equal_to<std::string>(), std::placeholders::_1, "han"));
    std::cout << *fir << std::endl;
    std::for_each(vec.cbegin(), vec.cend(), bind(std::plus<std::string>(), "pref", std::placeholders::_2));
    for (auto &c : vec) {
        std::cout << c << std::endl;
    }
    return 0;
}