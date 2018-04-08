//
// Created by qinhan on 2018/4/8.
//

#include "1444.h"
#include <iostream>
#include <map>
#include <functional>
#include <string>

int add(int a, int b) {
    return a + b;
}

int minus(int a, int b) {
    return a - b;
}

int multiplies(int a, int b) {
    return a * b;
}

int devides(int a, int b) {
    return a / b;
}

int main() {
    std::function<int(int, int)> f1 = add;
    std::function<int(int, int)> f2 = minus;
    std::function<int(int, int)> f3 = [](int a, int b) { return a * b; };
    std::function<int(int, int)> f4 = devides;
    std::map <std::string, std::function<int(int, int)>> maps = {
            {"+", f1},
            {"-", f2},
            {"*", f3},
            {"/", f4},
    };
    std::cout << maps["+"](10, 20) << std::endl;
    std::cout << maps["-"](10, 20) << std::endl;
    std::cout << maps["*"](10, 20) << std::endl;
    std::cout << maps["/"](100, 20) << std::endl;
    return 0;
}