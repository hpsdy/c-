//
// Created by qinhan on 2018/7/2.
//
#include "1612.h"

int main() {
    try {
        Blob<std::string> arr{"hello", "word"};
        Blob<std::string>::size_type size = arr.size();
        int i;
        for (i = 0; i < size; ++i) {
            printf("index:%d,value:%s\n", i, arr[i].c_str());
        }
    } catch (std::exception e) {
        printf("except:%s\n", e.what());
    } catch (...) {
        printf("except:%s\n", "δ֪�쳣");
    }
    return 0;
}

