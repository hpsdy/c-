#ifndef USER_STRING
#define USER_STRING
#include <memory>
#include <cstring>
#include <iostream>
namespace user {
    class String {
        friend String operator+(const String &str1, const String &str2);
        friend String add(const String &str1, const String &str2);
        friend std::iostream &operator<<(std::iostream &io, const String &str);
        friend void test() {
            std::cout << "friend func test" << endl;
        }
      public:
        String(): sz(0), first(nullptr) {}
        String(const char *p): sz(std::strlen(p)), first(alloc.allocate(sz)) {
            std::cout << "char construct" << std::endl;
            std::uninitialized_copy(p, p + sz, first);
        }
        String(const String &str): sz(str.size()), first(alloc.allocate(sz)) {
            std::cout << "string construct" << std::endl;
            std::uninitialized_copy(str.begin(), str.end(), first);
        }
        String *begin() const {
            std::cout << "const begin" << std::endl;
            return first;
        }
        String *end() const {
            std::cout << "const end" << std::endl;
            return first + sz;
        }
        String *begin() {
            std::cout << " begin" << std::endl;
            return first;
        }
        String *end() {
            std::cout << " end" << std::endl;
            return first + sz;
        }
      private:
        std::size_t sz;
        std::char *first;
        static std::allocator<std::char> alloc;
    };
    String add(const String &str1, const String &str2) {
        std::cout << "String add" << std::endl;
        String newStr;
        std::size_t size = str1.sz + str2.sz;
        newStr.sz = size;
        newStr.first = String::alloc.allocate(size);
        std::char *p = std::uninitialized_copy(str1.begin(), str1.end(), newStr.first);
        std::uninitialized_copy(str2.begin(), str2.end(), p);
        return newStr;
    }
    String operator+(const String &str1, const String &str2) {
        return add(str1, str2);
    }
    std::iostream &operator<<(std::iostream &io, const String &str) {
        std::cout << "operator<<" << endl;
        std::char *b = str.begin();
        while (b != str.end()) {
            io << *b++;
        }
        io << endl;
        return io;
    }
    //void test();
}
#endif