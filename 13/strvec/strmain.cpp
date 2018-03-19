#include "string.h"
#include "strVec.h"
#include <iostream>
//#include <cstdlib>
int main() {
    std::cout << "=======1=======" << std::endl;
    user::String s1("abc");
    std::cout << "=======2=======" << std::endl;
    user::String s2(s1);
    using user::String;
    std::cout << "=======3=======" << std::endl;
    String s3 = user::add(s1, s2);
    std::cout << "=======4=======" << std::endl;
    String s4 = s2 + s3;
    std::cout << "=======6=======" << std::endl;
    std::cout << s1;
    std::cout << "=======7=======" << std::endl;
    std::cout << s2;
    std::cout << "=======8=======" << std::endl;
    std::cout << s3;
    std::cout << "=======9=======" << std::endl;
    std::cout << s4;
    std::cout << "=======10=======" << std::endl;
    user::test();
    std::cout << "=======11=======" << std::endl;
    StrVec arr;
    arr.push_back(s1);
    arr.push_back(s2);
    arr.push_back(s3);
    arr.push_back(s4);
    for (auto b = arr.begin(), e = arr.end(); b != e; ++b) {
        std::cout << *b << std::endl;
    }
    return EXIT_SUCCESS;
}
