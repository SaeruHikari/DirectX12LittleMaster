#include "os/window.h"
#include <iostream>

#define DEFAULT_WIDTH 600
#define DEFAULT_HEIGHT 600

bool LittleWindow::Initialize(const wchar_t* title_)
{
    title = title_;
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    hWnd = createWin32Window(title.c_str());
    return hWnd;
}
bool LittleWindow::Destroy()
{
    return DestroyWindow(hWnd);
}

LRESULT CALLBACK WindowProcedure(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_DESTROY:
            std::cout << "destroying window\n";
            PostQuitMessage(0);
            return 0L;
        case WM_LBUTTONDOWN:
            std::cout << "mouse left button down at (" << LOWORD(lp) << ',' << HIWORD(lp) << ")\n";
        default:
            return DefWindowProc(window, msg, wp, lp);
    }
}
HWND LittleWindow::createWin32Window(const wchar_t* title)
{
    // Register the window class.
    auto myclass = TEXT("myclass");
    WNDCLASSEX wndclass = {
        sizeof(WNDCLASSEX), CS_DBLCLKS,
        WindowProcedure,
        0, 0, GetModuleHandle(0), LoadIcon(0, IDI_APPLICATION),
        LoadCursor(0, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
        0, myclass, LoadIcon(0, IDI_APPLICATION)
    };
    static bool bRegistered = RegisterClassEx(&wndclass);
    if (bRegistered)
    {
        HWND window = CreateWindowEx(0, myclass, title,
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, 0, GetModuleHandle(0), 0);
        if (window)
        {
            ShowWindow(window, SW_SHOWDEFAULT);
        }
        return window;
    }
    return nullptr;
}
