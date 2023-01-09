#ifndef TEST_COMMON_H
#define PRINT_LOG_H

#include <string>
#include <sstream>
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
template<typename ... Args>
std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
    formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
    strcpy(&formatted[0], fmt_str.c_str());
    va_start(ap, fmt_str);
    final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
    va_end(ap);
    if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
    else
            break;
    }
    return std::string(formatted.get());
}

/*
Usage: 
  Print_Log("Log Title", "Listening on port: %d.", port);
  Print_Log("Log Title", "Listening on Unix socket: %s", unix_socket);
  Print_Log("Log Title", "Log Content...");
*/
template<typename ... Args>
inline void Print_Log(const std::string log_title, const std::string log_fmt, Args... args) {

    std::cout << "[ *** ] [ " << log_title << " ] " << string_format(log_fmt, args...) << std::endl;
}

#endif
