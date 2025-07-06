#ifndef PIPER_H
#define PIPER_H

#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>
#include <cctype>
#include "vstructs.h"

#define PIPER_MAX 8048

class piper
{
public:
    piper();

    static std::string command   ( char* cmd);
    static std::string commandA  ( char* cmd);
    static wchar_t *chartowchar_t( char* cmd);
    static char *tchar_to_char(TCHAR* str);
    static v2str parseTasks  ( std::string in );
    static bool is_numerical ( std::string in );
};

#endif // PIPER_H
