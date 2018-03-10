#include "string.h"
#include <iostream>
#include <vector>
int main() {
    std::vector<String> arr;
    arr.push_back("abc");
    arr.push_back("qinhan");
    for (auto b = arr.begin(), e = arr.end(); b != e; ++b) {
        std::cout << *b << std::endl;
    }

    return EXIT_SUCCESS;
}