#pragma once
#include "configure.h"
#include "framework/object.h"
#include <string>

class LittleWindow : public LittleObject
{
public:
    LittleWindow(const wchar_t* title);
    ~LittleWindow() = default;

    virtual bool Initialize();
    virtual void Run() = 0;
    virtual bool Destroy();

protected:
    std::wstring title;
    UINT32 width;
    UINT32 height;
    HWND hWnd;
    HWND createWin32Window(const wchar_t* title);
};