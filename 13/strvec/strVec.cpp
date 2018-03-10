#include"strVec.h"
#include"string.h"
void strVec::push_back(const std::string &str) {
    check_n_alloc();
    alloc.construct(first_free++, str);
}
std::pair<std::string *, std::string *> strVec::alloc_n_copy(const std::string *b, const std::string *e) {
    std::string *p = alloc.allocate(e - b);
    return {p, std::uninitialized_copy(b, e, p)};
}
void strVec::free() {
    if (!elements) {
        return;
    }
    while (elements != first_free) {
        alloc.destroy(--first_free);
    }
    alloc.deallocate(elements, capacity());
}
strVec::strVec(const strVec &p) {
    auto data = alloc_n_copy(p.begin(), p.end());
    elements = data.first;
    first_free = cap = data.second;
}
strVec &strVec::operator=(const strVec &p) {
    auto data = alloc_n_copy(p.begin(), p.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void strVec::reallocate() {
    std::size_t newCapCity = size() ? 2 * size() : 1;
    std::string *p = alloc.allocate(newCapCity);
    auto dest = p;
    auto elem = elements;
    for (std::size_t i = 0, num = size(); i < num; ++i) {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = p;
    first_free = dest;
    cap = p + newCapCity;

}



void StrVec::push_back(const String &str) {
    check_n_alloc();
    alloc.construct(first_free++, str);
}
std::pair<String *, String *> StrVec::alloc_n_copy(const String *b, const String *e) {
    String *p = alloc.allocate(e - b);
    return {p, std::uninitialized_copy(b, e, p)};
}
void StrVec::free() {
    if (!elements) {
        return;
    }
    while (elements != first_free) {
        alloc.destroy(--first_free);
    }
    alloc.deallocate(elements, capacity());
}
StrVec::StrVec(const StrVec &p) {
    auto data = alloc_n_copy(p.begin(), p.end());
    elements = data.first;
    first_free = cap = data.second;
}
StrVec &StrVec::operator=(const StrVec &p) {
    auto data = alloc_n_copy(p.begin(), p.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate() {
    std::size_t newCapCity = size() ? 2 * size() : 1;
    String *p = alloc.allocate(newCapCity);
    auto dest = p;
    auto elem = elements;
    for (std::size_t i = 0, num = size(); i < num; ++i) {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = p;
    first_free = dest;
    cap = p + newCapCity;

}
std::allocator<std::string> strVec::alloc;
std::allocator<String> StrVec::alloc;

namespace user {
    String add(const String &str1, const String &str2) {
        std::cout << "String add" << std::endl;
        String newStr;
        std::size_t size = str1.sz + str2.sz;
        newStr.sz = size;
        newStr.first = String::alloc.allocate(size);
        char *p = std::uninitialized_copy(str1.begin(), str1.end(), newStr.first);
        std::uninitialized_copy(str2.begin(), str2.end(), p);
        return newStr;
    }
    String operator+(const String &str1, const String &str2) {
        std::cout << "operator +" << std::endl;
        return add(str1, str2);
    }
    std::ostream &operator<<(std::ostream &io, const String &str) {
        std::cout << "operator<<" << std::endl;
        char *b = str.begin();
        char *e = str.end();
        while (b != e) {
            io << *b++;
        }
        io << std::endl;
        return io;
    }
    //void test();
    std::allocator<char> String::alloc;
}
//void user::test();
