#pragma once
#include "os/window.h"
#include <vector>

class LittleGFXAdapter
{
    friend class LittleGFXWindow;
    friend class LittleGFXInstance;
    friend class LittleGFXDevice;

protected:
    LittleGFXInstance* instance;
    struct IDXGIAdapter4* pDXGIAdapter;
};

class LittleGFXInstance
{
    friend class LittleGFXWindow;
    friend class LittleGFXInstance;
    friend class LittleGFXDevice;

public:
    bool Initialize(bool enableDebugLayer);
    bool Destroy();

    uint32_t GetAdapterCount() const { return adapters.size(); }
    LittleGFXAdapter* GetAdapter(uint32_t idx) { return &adapters[idx]; }

protected:
    void queryAllAdapters();
    bool debugLayerEnabled;
    struct IDXGIFactory6* pDXGIFactory = nullptr;
    std::vector<LittleGFXAdapter> adapters;
    bool foundSoftwareAdapter;
};

class LittleGFXDevice
{
    friend class LittleGFXWindow;

public:
    bool Initialize(LittleGFXAdapter* adapter);
    bool Destroy();

protected:
    LittleGFXAdapter* adapter;
    struct ID3D12Device* pD3D12Device;
    struct ID3D12CommandQueue* pD3D12Queue;
};

class LittleGFXWindow : public LittleWindow
{
    friend class LittleGFXInstance;

public:
    bool Initialize(const wchar_t* title, LittleGFXDevice* device, bool enableVsync);
    bool Destroy();

protected:
    void createDXGISwapChain(struct IDXGIFactory6* pDXGIFactory, struct ID3D12CommandQueue* present_queue);
    bool vsyncEnabled = false;
    uint32_t swapchainFlags;
    struct IDXGISwapChain3* pSwapChain = nullptr;
};