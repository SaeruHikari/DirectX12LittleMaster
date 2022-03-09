#pragma once
#include "os/window.h"
#include <vector>

class LittleGFXInstance
{
    friend class LittleGFXWindow;

public:
    bool Initialize(bool enableDebugLayer);
    bool Destroy();

protected:
    void queryAllAdapters();
    bool debugLayerEnabled;
    struct IDXGIFactory6* pDXGIFactory = nullptr;
    std::vector<struct IDXGIAdapter4*> mDXGIAdapters;
    bool foundSoftwareAdapter;
};

class LittleGFXWindow : public LittleWindow
{
    friend class LittleGFXInstance;

public:
    bool Initialize(const wchar_t* title, LittleGFXInstance* dxgiInst, bool enableVsync);
    bool Destroy();

protected:
    void createDXGISwapChain();
    bool vsyncEnabled = false;
    uint32_t swapchainFlags;
    struct IDXGISwapChain3* pSwapChain = nullptr;
    LittleGFXInstance* dxgiInstance = nullptr;
};