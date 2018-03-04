#include "string.h"
#include <iostream>
#include <cstdlib>
int main() {
    user::String s1("abc");
    user::String s2(s1);
    using user::String;
    String s3 = add(s1, s2);
    String s4("qinhan");
    s4 = s4 + s3;
    std::cout << s1;
    std::cout << s2;
    std::cout << s3;
    std::cout << s4;
    user::test();
    return EXIT_SUCCESS;
}