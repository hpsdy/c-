#include "string.h"
#include <iostream>
#include <cstdlib>
int main() {
    std::cout << "=======1=======" << std::endl;
    user::String s1("abc");
    std::cout << "=======2=======" << std::endl;
    user::String s2(s1);
    using user::String;
    std::cout << "=======3=======" << std::endl;
    String s3 = add(s1, s2);
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
    return EXIT_SUCCESS;
}