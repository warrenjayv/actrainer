#include "piper.h"

piper::piper() {}

std::string piper::command(char* cmd)
{
    wchar_t* _ws = new wchar_t[strlen(cmd)+ 1];

    HANDLE _rpipe = NULL;
    HANDLE _wpipe = NULL;

    SECURITY_ATTRIBUTES _sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    if (! CreatePipe(&_rpipe, &_wpipe, &_sa, 0))
    {
        return "ERROR - failed to create pipe";
    }

    STARTUPINFO _si = { 0 };

    _si.hStdInput = _wpipe;
    _si.dwFlags   = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION _pi = { 0 };

    if (! CreateProcess( NULL, _ws, NULL, NULL, TRUE, 0, NULL, NULL, &_si, &_pi ))
    {
        return "ERROR - failed to create process";
    }

    WaitForSingleObject(_pi.hProcess, INFINITE);

    char  _buffer[1024];
    DWORD _bytes_read = 0;

    std::string _out = "";

    while(ReadFile(_rpipe, &_buffer, sizeof(_buffer), &_bytes_read, NULL) && _bytes_read > 0)
    {
        _out.append(_buffer, _bytes_read);
    }

    return _out;

}
