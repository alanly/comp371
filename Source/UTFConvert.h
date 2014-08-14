#pragma once

#include <cwchar>
#include <string>
#include <stdio.h>
#include <Windows.h>
using namespace std;

class UTFConvert {
public:
    UTFConvert();
    ~UTFConvert();
    static wchar_t * UTF8_to_WChar(const char *string);
    static char * WChar_to_UTF8(const wchar_t *string);
    static bool Replace(std::string& str, const std::string& from, const std::string& to);
    static string GetImagePath(const char * imgName);
};
