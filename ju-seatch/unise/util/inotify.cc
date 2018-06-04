// inotify 接口的具体实现。在高版本的 libc 中此接口是集成到 glibc 中的，
// 但由于开发、测试、线上机的操作系统发行版限制，我们无法使用高版本
// glibc，只好自己进行裸系统调用。
#include "inotify.h"

#include <sys/syscall.h>
#include <unistd.h>

// 拷贝自新版本的宏定义，旧版本的 syscall.h 中极有可能没有下面的宏定义
// 我们仅支持 __x86_64__ 平台
#ifndef __NR_inotify_init
#ifdef __x86_64__
#define __NR_inotify_init               253
#define __NR_inotify_add_watch          254
#define __NR_inotify_rm_watch           255
#define __NR_inotify_init1              294
#endif  // __x86_64__
#endif  // __NR_inotify_init

#ifndef SYS_inotify_init
#define SYS_inotify_init        __NR_inotify_init
#define SYS_inotify_init1       __NR_inotify_init1
#define SYS_inotify_add_watch   __NR_inotify_add_watch
#define SYS_inotify_rm_watch    __NR_inotify_rm_watch
#endif  // SYS_inotify_init

int inotify_init(void) __THROW {
    return syscall(SYS_inotify_init);
}

int inotify_init1(int __flags) __THROW {
    return syscall(SYS_inotify_init1, __flags);
}

int inotify_add_watch(int __fd, const char *__name, uint32_t __mask) __THROW {
    return syscall(SYS_inotify_add_watch, __fd, __name, __mask);
}

int inotify_rm_watch(int __fd, int __wd) __THROW {
    return syscall(SYS_inotify_rm_watch, __fd, __wd);
}
