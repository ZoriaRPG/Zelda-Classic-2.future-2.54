
#pragma once

#ifdef _WIN32


#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <allegro.h>
#include <winalleg.h>



class Win32Data
{
public:
    volatile HWND hWnd;
    volatile LONG_PTR hInstance;
    volatile LONG_PTR hId;
    
    static LRESULT CALLBACK zqWindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static int zqSetDefaultThreadPriority(HANDLE _thread);
    static int zqSetCustomCallbackProc(HWND hWnd);
    
    static LRESULT CALLBACK zcWindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static int zcSetCustomCallbackProc(HWND hWnd);
    
    volatile bool hasFocus;
    volatile bool isValid;
    
    //call from main thread.
    void Update(int frameskip);
};
extern Win32Data win32data;



class Win32Mutex
{
public:
    Win32Mutex(bool lock = false) : m_locked(false)
    {
        ::InitializeCriticalSection(&m_criticalSection);
        
        if(lock)
            Lock();
    }
    
    ~Win32Mutex()
    {
        Unlock();
        ::DeleteCriticalSection(&m_criticalSection);
    }
    
    void Lock()
    {
        if(!m_locked)
        {
            m_locked = true;
            ::EnterCriticalSection(&m_criticalSection);
        }
    }
    
    void Unlock()
    {
        if(m_locked)
        {
            m_locked = false;
            ::LeaveCriticalSection(&m_criticalSection);
        }
    }
    
protected:
    CRITICAL_SECTION m_criticalSection;
    bool m_locked;
};













#endif //_WIN32
