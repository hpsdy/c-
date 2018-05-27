//
// Created by hupose on 2018/5/27.
//
#include<cstdio>

int main(int argc, char *argv[]) {
    char opt = '\0';
    while (((opt = getopt(argc, args, "c:hv")) != -1)) {
        switch (opt) {
            case 'c':
                printf("c:%s", optarg);
                break;
            case 'h':
                printf("h:%s", optarg);
                break;
            case 'v':
                printf("v:%s", optarg);
                break;
            case '?':
                printf("?:%s", optarg);
                printf("??:%s", optopt);
                break;
            default:
                print_usage();
                break;
        }
    }
    return 0;
}
