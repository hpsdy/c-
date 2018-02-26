#include<iostream>
#include<utility>
using namespace std;
int main() {
    const int  &a = 100;
    cout << a << endl;
    int &&c = 20;
    int &&b = std::move(c);
    cout << b << endl;
    cout << c << endl;
    b = 99;
    cout << "=-=" << endl;
    cout << &b << endl;
    cout << &c << endl;
    cout << b << endl;
    cout << c << endl;
    c = 10000;
    cout << &b << endl;
    cout << &c << endl;
    cout << b << endl;
    cout << c << endl;
    return 0;
}
