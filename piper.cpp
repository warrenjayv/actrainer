#include "piper.h"

piper::piper() {}

char * piper::tchar_to_char( TCHAR* str )
{
    if (! str) { return nullptr; }

    char* _c = new char[MAX_PATH];

    WideCharToMultiByte(CP_ACP, 0, str, -1, _c, MAX_PATH, NULL, NULL);
    return _c;
}

wchar_t * piper::chartowchar_t( char* cmd )
{
    int _sz = MultiByteToWideChar(CP_ACP, 0, cmd, -1, NULL, 0);
    if (_sz == 0)
    {
        return nullptr;
    }

    wchar_t* _ws = new wchar_t[_sz];

    int _cc = MultiByteToWideChar(CP_ACP, 0, cmd, -1, _ws, _sz);

    if ( _cc == 0 )
    {
        delete[] _ws;
        return nullptr;
    }


    return _ws;
}

std::string piper::command(char* cmd)
{
    wchar_t* _ws = piper::chartowchar_t(cmd);

    if (_ws == NULL)
    {
        return "ERROR - invalid command";
    }

    HANDLE _rpipe = NULL;
    HANDLE _wpipe = NULL;

    SECURITY_ATTRIBUTES _sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    if (! CreatePipe(&_rpipe, &_wpipe, &_sa, 0))
    {
        return "ERROR - failed to create pipe";
    }

    STARTUPINFO _si;
    ZeroMemory(&_si, sizeof(_si));

    _si.cb        = sizeof(_si);
    _si.hStdInput = _wpipe;
    _si.dwFlags   = STARTF_USESTDHANDLES;
    _si.hStdError = _wpipe;

    PROCESS_INFORMATION _pi;
    ZeroMemory(&_pi, sizeof(_pi));

    if (! CreateProcess( NULL, _ws, NULL, NULL, TRUE, 0, NULL, NULL, &_si, &_pi ))
    {
        CloseHandle(_wpipe);
        CloseHandle(_rpipe);
        return "ERROR - failed to create process ";
    }

    CloseHandle(_wpipe);

    char  _buffer[PIPER_MAX];
    DWORD _bytes_read = 0;

    std::string _out = "";

    while(ReadFile(_rpipe, &_buffer, sizeof(_buffer), &_bytes_read, NULL) && _bytes_read > 0)
    {
        DWORD error = GetLastError();
        if (error == ERROR_BROKEN_PIPE)
        {
            return "ERROR - broken pipe";
            break;
        }
        _out.append(_buffer, _bytes_read);

    }

    WaitForSingleObject(_pi.hProcess, INFINITE);

    CloseHandle(_pi.hProcess);
    CloseHandle(_pi.hThread);
    CloseHandle(_rpipe);

    return _out;

}

std::string piper::commandA(char* cmd)
{
    FILE *_pip = popen(cmd, "r");
    if (!_pip)
    {
        return "ERROR : popen failed";
    }

    char buffer[1024];

    std::string result = "";

    while(fgets(buffer, sizeof(buffer), _pip) != nullptr)
    {
        result += buffer;
    }

    pclose(_pip);
    return result;
}

v2str piper::parseTasks( std::string in )
{
    v2str _v2;
    std::string _v;
    std::istringstream iss(in);
    bool _getNxt = false;

    while( iss >> _v )
    {
        if (_v.find(".exe") != std::string::npos)
        {
            _v2.a.push_back(_v);
            _getNxt = true;
            continue;
        }

        if ( _getNxt )
        {
            if (piper::is_numerical(_v) )
            {
                _v2.b.push_back(_v);
            }

            _getNxt = false;
        }
    }

    return _v2;

    /*
    for( int i = 0; i < _a.size(); i++)
    {
      std::cout << _a[i] << " " << _b[i] << std::endl;
    }
    */

}

bool piper::is_numerical ( std::string in )
{
    for ( char c : in )
    {
        if (! isdigit(c))
        {
            return false;
        }
    }
    return true;
}

