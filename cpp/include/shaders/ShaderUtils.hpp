#pragma once

#include <string>
#include <Windows.h>

// Convert various string-like inputs to std::string.
// If ty_string is const char* or std::string this will work.
// If ty_string is different, adapt ToStdString usage in callers.
static inline std::string ToStdString(const std::string& s) { return s; }
static inline std::string ToStdString(const char* s) { return s ? std::string(s) : std::string(); }

// Convert UTF-8 std::string to std::wstring (LPCWSTR)
static inline std::wstring ToWString(const std::string& s)
{
    if (s.empty()) return std::wstring();
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);
    if (len <= 0) return std::wstring();
    std::wstring w;
    w.resize(len);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &w[0], len);
    return w;
}
