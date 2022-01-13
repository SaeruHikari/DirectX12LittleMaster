#pragma once
#include "os/window.h"
#include <vector>

class LittleDXGIInstance : public LittleObject
{
    friend class LittleDXGIWindow;
public:
    LittleDXGIInstance(bool enableDebugLayer);
    ~LittleDXGIInstance() = default;

    virtual bool Initialize() override;
    virtual bool Destroy() override;
protected:
    void queryAllAdapters();
    bool debugLayerEnabled;
    struct IDXGIFactory6* pDXGIFactory = nullptr;
    std::vector<struct IDXGIAdapter4*> mDXGIAdapters;   
    bool foundSoftwareAdapter; 
};

class LittleDXGIWindow : public LittleWindow
{
    friend class LittleDXGIInstance;
public:
    inline LittleDXGIWindow(const wchar_t* title, 
        LittleDXGIInstance* dxgiInst, bool enableVsync) 
        :LittleWindow(title), vsyncEnabled(enableVsync), dxgiInstance(dxgiInst) {}
    
    virtual bool Initialize() override;
    virtual bool Destroy() override;
protected:
    void createDXGISwapChain();
    bool vsyncEnabled = false;
    uint32_t swapchainFlags;
    struct IDXGISwapChain3* pSwapChain = nullptr;
    LittleDXGIInstance* dxgiInstance = nullptr;
};