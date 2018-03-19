#include <iostream>
#include <utility>
#include <memory>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int main() {
    char a[] = "abc";
    size_t len = strlen(a);
    cout << "a len:" << len << endl;
    allocator<char> alloc;
    char *p = alloc.allocate(len);
    uninitialized_copy(a, a + len, p);
    cout << "p:" << p << endl;

    vector<string> strarr{"qin", "han", "cool"};
    auto sb = strarr.begin();
    size_t size = strarr.size();
    string *strb = &(*sb);
    string *stre = strb + size;
    cout << "str begin:" << strb << ":" << *strb << endl;
    cout << "str end:" << stre << ":" << *stre << endl;
    allocator<string> strAlloc;
    string *strp = strAlloc.allocate(size);
    uninitialized_copy(strb, stre, strp);
    while (size) {
        cout << *strp++ << endl;
    }
    return EXIT_SUCCESS;

}