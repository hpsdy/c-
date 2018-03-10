#include "string.h"
#include <iostream>
#include <vector>
#include <cstdlib>
int main() {
    std::vector<user::String> arr;
    arr.push_back("abc");
    std::cout << "================" << std::endl;
    user::String str = "qinhan";
    arr.push_back(str);
    std::cout << "================" << std::endl;
    user::String str1 = "dashuaige";
    arr.push_back(std::move(str));
    for (auto b = arr.begin(), e = arr.end(); b != e; ++b) {
        std::cout << *b << std::endl;
    }

    return EXIT_SUCCESS;
}