#ifndef AUTOCONTOUR_DEBUG_MACRO_H
#define AUTOCONTOUR_DEBUG_MACRO_H

#include <iostream>
#include <sstream>
#include <iomanip>

//
// Khi không cần in ra log nữa ta đơn giản định nghĩa macro DEBUG (tức là Debug) bằng dòng bên dưới.
// Khi biên dich, các đoạn mã trống do {} while(0); sẽ bị xóa hết do tối ưu.
// Vì thế hầu như không ảnh hưởng đến code chính.
#define DEBUG (1)


// color https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

template<typename Arg, typename... Args>
void doPrint(const char *type,
        const char *file,
        const char *func,
        int line,
        const char *color,
        Arg &&arg,
        Args &&... args) {
    std::string s(func);
    s += ":" + std::to_string(line);
    std::cout << "\033[1;" << color << std::left << std::setw(9) << type << " | "
              << std::left << std::setw(20) << file << " | "
              << std::left << std::setw(20) << s << " | " << std::forward<Arg>(arg);

    using expander = int[];
    (void) expander{0, (void(std::cout << std::forward<Args>(args)), 0)...};
    std::cout << "\033[0m";
}

#ifndef DEBUG
#define log_debug(f, ...)  do {} while (0)
#define log_err(f, ...)  do {} while (0)
#define log_warn(f, ...)  do {} while (0)
#define log_info(f, ...)  do {} while (0)
#else // DEBUG

//
// Dành cho việc in ra log debug
//

#define log_debug(f, ...)\
        do { doPrint("[DEBUG]", __FILENAME__, __func__, __LINE__ , "34m", f, ## __VA_ARGS__); } while (0)

//
// Dành cho việc  in ra log lỗi
//
#define log_err(f, ...) \
        do { doPrint("[ERROR]", __FILENAME__, __func__, __LINE__ , "31m", f, ## __VA_ARGS__); } while (0)

//
// Dành cho việc in ra log lỗi
//
#define log_warn(f, ...) \
        do { doPrint("[WARNING]", __FILENAME__, __func__, __LINE__ , "93m", f, ## __VA_ARGS__); } while (0)
//
// Dành cho việc in ra các thông tin khác.
//
#define log_info(f, ...) \
        do { doPrint("[INFO]", __FILENAME__, __func__, __LINE__ , "92m", f, ## __VA_ARGS__); } while (0)
#endif //NDEBUG

#endif //AUTOCONTOUR_DEBUG_MACRO_H
