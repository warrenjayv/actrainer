#include "piper.h"

piper::piper() {}

std::string piper::command(char* cmd)
{
    HANDLE _rpipe = NULL;
    HANDLE _wpipe = NULL;

    SECURITY_ATTRIBUTES _sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    if (! CreatePipe(&_rpipe, &_wpipe, &_sa, 0))
    {
        return "ERROR - failed to create pipe";
    }
}
