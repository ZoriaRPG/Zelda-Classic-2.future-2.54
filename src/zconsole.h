#ifndef _zc_win_console_h_
#define _zc_win_console_h_


#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>


#ifdef _MSC_VER
#pragma warning ( disable : 4996 )
#endif



class DebugConsole //Really half-ass singleton class. Do not instantiate this object.
{
private:
    bool isOpen;
    static DebugConsole singleton;
public:
    DebugConsole() : isOpen(false)
    {
    }
    
    ~DebugConsole()
    {
        Close();
    }
    
    static void Close()
    {
        if(singleton.isOpen)
            ::FreeConsole();
            
        singleton.isOpen = false;
    }
    
    static void Open()
    {
        if(singleton.isOpen)
            return;
            
        singleton.isOpen = true;
        
        const int MAX_CONSOLE_LINES = 512;
        
        CONSOLE_SCREEN_BUFFER_INFO console_info;
        int hConHandle;
        long lStdHandle;
        
        ::AllocConsole();
        ::SetConsoleTitle("zconsole");
        
        
        // set the screen buffer to be big enough to scroll text
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_info);
        console_info.dwSize.Y = MAX_CONSOLE_LINES;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), console_info.dwSize);
        
        
        // redirect unbuffered STDOUT to the console
        lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        *stdout = *_fdopen(hConHandle, "w");
        setvbuf(stdout, NULL, _IONBF, 0);
        
        
        // redirect unbuffered STDIN to the console
        lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        *stdin = *_fdopen(hConHandle, "r");
        setvbuf(stdin, NULL, _IONBF, 0);
        
        
        // redirect unbuffered STDERR to the console
        lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        *stderr = *_fdopen(hConHandle, "w");
        setvbuf(stderr, NULL, _IONBF, 0);
        
        
        //for cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
        std::ios::sync_with_stdio();
    }
    
};


#ifdef _MSC_VER
#pragma warning ( default : 4996 )
#endif


#else // _WIN32

class DebugConsole
{
public:
    static void Open() {}
    static void Close() {}
    static DebugConsole singleton;
};

#endif // not _WIN32

#endif

