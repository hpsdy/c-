#ifndef UTIL_GLOBAL_INIT_H
#define UTIL_GLOBAL_INIT_H

namespace unise {
/**
 * @brief 全局的初始化函数，为了尽量保证其通用性，暂时不往里面放非通用的
 *        初始化内容，我们希望它能够作为基础库的头文件。
 */ 
class GlobalInit {
public:
    GlobalInit() {}
    ~GlobalInit() {}
    static void global_init(int argc, char *argv[]);
};
}

#endif // UTIL_GLOBAL_INIT_H
