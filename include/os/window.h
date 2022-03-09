#pragma once
#include "configure.h"
#include "framework/object.h"
#include <string>

class LittleWindow
{
public:
    bool Initialize(const wchar_t* title);
    virtual void Run() = 0;
    bool Destroy();

protected:
    std::wstring title;
    UINT32 width;
    UINT32 height;
    HWND hWnd;
    HWND createWin32Window(const wchar_t* title);
};