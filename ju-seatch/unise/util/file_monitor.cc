#include "util/file_monitor.h"

#include "unise/base.h"

namespace unise
{

// 超时时间设为1秒或以下是比较合适的值，时间长了影响进程正常退出，时间短了会使线程频繁唤醒
FileMonitor::FileMonitor()
    : Thread("FileMonitor"), _timeout_ms(1000), _sig_exit(false)
{
    _watch_fd = inotify_init();
    REGISTER_HANDLER(on_exit, FileMonitor, _on_exit);
}

FileMonitor::~FileMonitor()
{
    wd_map_t::iterator it;
    for (it = _wd_map.begin(); it != _wd_map.end(); ++it) {
        inotify_rm_watch(_watch_fd, it->first);
    }
}

bool FileMonitor::register_fcb(const std::string& path, Closure* callback)
{
    boost::unique_lock<boost::shared_mutex> lock(_mutex);
    boost::shared_ptr<Closure> cb_ptr(callback);
    // 如果路径已经在监控中，那么仅追加回调即可
    path_map_t::iterator info = _path_map.find(path);
    if (info != _path_map.end()) {
        info->second.callbacks.push_back(cb_ptr);
    } else {
        // 否则，先验证添加 inotify，然后再添加到路径表中
        fm_info_t fm_info;
        fm_info.wd = inotify_add_watch(_watch_fd, path.c_str(), WATCH_IN_EVENTS);
        // 如果在注册的时候 inotify 无法添加，说明路径不可读，出错返回
        if (fm_info.wd < 0) {
            UWARNING("[\tlvl=SERIOUS\t] inotify_add_watch(fd=%d, name=%s) err(%m)",
                    _watch_fd, path.c_str());
            return false;
        }
        fm_info.callbacks.push_back(cb_ptr);
        _path_map.insert(std::make_pair(path, fm_info));
        _wd_map.insert(std::make_pair(fm_info.wd, path));
    }
    return true;
}

void FileMonitor::remove_fcb(const std::string &path)
{
    boost::unique_lock<boost::shared_mutex> lock(_mutex);
    path_map_t::iterator info = _path_map.find(path);
    if (info != _path_map.end()) {
        inotify_rm_watch(_watch_fd, info->second.wd);
        _wd_map.erase(info->second.wd);
        _path_map.erase(info);
    }
}

int FileMonitor::run()
{
    while (!_sig_exit) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(_watch_fd, &fds);
        timeval to = {0, _timeout_ms * 1000};
        if (select(_watch_fd + 1, &fds, NULL, NULL, &to) > 0) {
            ssize_t offset = 0;
            unsigned char buf[READ_BUFLEN] = {0};
            ssize_t total_len = read(_watch_fd, &buf, sizeof(buf));
            if (total_len > 0) {
                while (offset < total_len) {
                    inotify_event *event = reinterpret_cast<inotify_event *>(buf + offset);
                    offset += sizeof(inotify_event) + event->len;
                    // 收到了需要处理的回调信号
                    if (event->mask & HANDLE_IN_EVENTS) {
                        UTRACE("Detect an inotify event(wd=%d, mask=%u, name=%s)",
                                event->wd, event->mask, event->name);
                        _handle_event(event->wd, event->mask);
                    } else {
                        UTRACE("Ignore an inotify event(wd=%d, mask=%u, name=%s)",
                                event->wd, event->mask, event->name);
                    }
                }
            }
        }
        // 处理那些 inode 失效的路径，查看是否有新的文件在同一路径下生成
        _handle_fail();
    }
    return 0;
}

void FileMonitor::_handle_event(int wd, uint32_t mask)
{
    boost::unique_lock<boost::shared_mutex> lock(_mutex);
    wd_map_t::iterator wd_iter = _wd_map.find(wd);
    if (wd_iter != _wd_map.end()) {
        std::string path = wd_iter->second;
        path_map_t::iterator path_iter = _path_map.find(path);
        if (path_iter != _path_map.end()) {
            UTRACE("Handle an inotify event(wd=%d, mask=%u, path=%s, callbacks=%lu)",
                    wd, mask, path.c_str(), path_iter->second.callbacks.size());
            // 执行所有相关的回调
            for (size_t i = 0; i < path_iter->second.callbacks.size(); ++i) {
                path_iter->second.callbacks[i]->Run();
            }
            // 如果事件是文件被移动、删除等，标记回调为空
            if (mask & (IN_DELETE_SELF | IN_MOVE | IN_IGNORED)) {
                UNOTICE("path removed (path=%s, mask=%u)", path.c_str(), mask);
                _wd_map.erase(wd_iter);
                inotify_rm_watch(_watch_fd, wd);
                path_iter->second.wd = -1;
                _fail_paths.push_back(path);
            }
        } else {
            // 找不到路径对应的回调
            inotify_rm_watch(_watch_fd, wd);
            _wd_map.erase(wd_iter);
        }
    } else {
        // 找不到 watch 对应的路径
        inotify_rm_watch(_watch_fd, wd);
    }
}

void FileMonitor::_handle_fail()
{
    boost::unique_lock<boost::shared_mutex> lock(_mutex);
    std::vector<std::string>::iterator it = _fail_paths.begin();
    // 遍历所有失效的监控文件路径
    while (it != _fail_paths.end()) {
        path_map_t::iterator path_it = _path_map.find(*it);
        if (_path_map.end() != path_it) {
            int &wd = path_it->second.wd;
            wd = inotify_add_watch(_watch_fd, it->c_str(), WATCH_IN_EVENTS);
            // 在新文件上添加监控成功，同时执行回调函数知晓新文件的改动
            if (wd > 0) {
                UNOTICE("path created (%s)", it->c_str());
                _wd_map.insert(std::make_pair(wd, *it));
                // 执行所有相关的回调
                for (size_t j = 0; j < path_it->second.callbacks.size(); ++j) {
                    path_it->second.callbacks[j]->Run();
                }
                it = _fail_paths.erase(it);
            } else {
                ++it;
            }
        } else {
            it = _fail_paths.erase(it);
        }
    }
}

}   // namespace unise
