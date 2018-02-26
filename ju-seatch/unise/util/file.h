#ifndef UTIL_FILE_H_
#define UTIL_FILE_H_

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <unistd.h>
#include <vector>

namespace unise
{

/// @brief 类似于 boost::filesystem，提供一些基本操作；但由于 boost::filesystem 比较完善，
/// 对正确的 locale 依赖比较严重，这里暂不使用 boost::filesystem。
class FileSystem
{
public:
    static bool is_dir(const std::string &path) {
        struct stat st;
        if (0 == lstat(path.c_str(), &st)) {
            return S_ISDIR(st.st_mode);
        } else {
            return false;
        }
    }
    /// @brief 得到一个路径的所有子路径，即原路径拼接上子目录
    /// @param path
    /// @param subpaths
    /// @return
    static bool get_sub_paths(const std::string &path, std::vector<std::string> *subpaths) {
        if (subpaths) {
            subpaths->clear();
            std::string subpath;
            DIR *dir = opendir(path.c_str());
            if (dir) {
                dirent de;
                dirent* res = NULL;
                while ((readdir_r(dir, &de, &res) == 0) && res) {
                    // 忽略隐藏的路径
                    if ('.' != res->d_name[0]) {
                        subpath = path + "/" + res->d_name;
                        subpaths->push_back(subpath);
                    }
                }
                closedir(dir);
                return true;
            }
        }
        return false;
    }

    /// @brief 判断一个文件是否存在
    /// @param file_name 文件全路径
    /// @return true 存在，false 不存在
    static bool is_file_exist(const std::string &file_name) {
        return 0 == access(file_name.c_str(), F_OK);
    }

private:
};

}   // namespace unise

#endif  // UTIL_FILE_H_
