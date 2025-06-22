#ifndef PIPER_H
#define PIPER_H

#include <windows.h>
#include <iostream>
#include <string>

class piper
{
public:
    piper();

    static std::string command( char* cmd );
};

#endif // PIPER_H
