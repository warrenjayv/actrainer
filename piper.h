#ifndef PIPER_H
#define PIPER_H

#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>

#define PIPER_MAX 8048

class piper
{
public:
    piper();

    static std::string command   ( char* cmd);
    static std::string commandA  ( char* cmd);
    static wchar_t *chartowchar_t( char* cmd);
};

#endif // PIPER_H
