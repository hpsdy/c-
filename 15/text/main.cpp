//
// Created by hupose on 2018/5/27.
//
#include<cstdio>

int main(int argc, char *argv[]) {
    char opt = '\0';
    while (((opt = getopt(argc, args, "c:hv")) != -1)) {
        switch (opt) {
            case 'c':
                printf("c:%s\n", optarg);
                break;
            case 'h':
                printf("h:%s\n", optarg);
                break;
            case 'v':
                printf("v:%s\n", optarg);
                break;
            case '?':
                printf("?:%s\n", optarg);
                printf("??:%s\n", optopt);
                break;
            default:
                printf("defalut:%s,default:%s\n", optarg, optopt);
                break;
        }
    }
    return 0;
}
