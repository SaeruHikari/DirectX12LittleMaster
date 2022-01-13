#include "gfx/dxgi_objects.h"
#include <vector>
#include <dxgi1_6.h>
#include <iostream>

// 链接到dxgi库
#pragma comment(lib, "dxgi.lib")

LittleDXGIInstance::LittleDXGIInstance(bool enableDebugLayer)
    :debugLayerEnabled(enableDebugLayer)
{

}

bool LittleDXGIInstance::Initialize()
{
    UINT flags = 0;
    if (debugLayerEnabled) flags = DXGI_CREATE_FACTORY_DEBUG;
    if (SUCCEEDED(CreateDXGIFactory2(flags, IID_PPV_ARGS(&pDXGIFactory))))
    {
        queryAllAdapters();
        // If the only adapter we found is a software adapter, log error message for QA
        if (!mDXGIAdapters.size() && foundSoftwareAdapter)
        {
            assert(0 && "The only available GPU has DXGI_ADAPTER_FLAG_SOFTWARE. Early exiting");
            return false;
        }
    }
    else
    {
        assert("[D3D12 Fatal]: Create DXGIFactory2 Failed!");
        return false;
    }
    return true;
}

bool LittleDXGIInstance::Destroy()
{
    for(auto iter : mDXGIAdapters)
    {
        SAFE_RELEASE(iter);
    }
    SAFE_RELEASE(pDXGIFactory);
    return true;
}

void LittleDXGIInstance::queryAllAdapters()
{
    IDXGIAdapter4* adapter = NULL;
    // Use DXGI6 interface which lets us specify gpu preference so we dont need to use NVOptimus or AMDPowerExpress
    for (UINT i = 0;
         pDXGIFactory->EnumAdapterByGpuPreference(i,
             DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
             IID_PPV_ARGS(&adapter)) != DXGI_ERROR_NOT_FOUND;
         i++)
    {
        DXGI_ADAPTER_DESC3 desc = { 0 };
        adapter->GetDesc3(&desc);
        std::wcout << desc.Description << std::endl;
        if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            foundSoftwareAdapter = true;
        }
        else
            mDXGIAdapters.push_back(adapter);
    }
}

bool LittleDXGIWindow::Initialize()
{
    auto succeed = LittleWindow::Initialize();
    createDXGISwapChain();
    return succeed;
}

bool LittleDXGIWindow::Destroy()
{
    auto succeed = LittleWindow::Destroy();
    SAFE_RELEASE(pSwapChain);
    return succeed;
}

void LittleDXGIWindow::createDXGISwapChain()
{
    DXGI_SWAP_CHAIN_DESC1 chain_desc1 = {0};
    chain_desc1.Width = width;
    chain_desc1.Height = height;
    // https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1
    chain_desc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    chain_desc1.Stereo = false;
    chain_desc1.SampleDesc.Count = 1; // If multisampling is needed, we'll resolve it later
    chain_desc1.SampleDesc.Quality = 0;
    chain_desc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    chain_desc1.BufferCount = vsyncEnabled ? 3 : 2;
    chain_desc1.Scaling = DXGI_SCALING_STRETCH;
    chain_desc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // for better performance.
    chain_desc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    chain_desc1.Flags = 0;
    
    BOOL allowTearing = FALSE;
    chain_desc1.Flags |= allowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
    swapchainFlags |= (!vsyncEnabled && allowTearing) ? DXGI_PRESENT_ALLOW_TEARING : 0;

    if (false)
    {    
        IDXGISwapChain1* swapchain;
        auto bCreated = SUCCEEDED(dxgiInstance->pDXGIFactory->CreateSwapChainForHwnd(NULL,
            hWnd, &chain_desc1, NULL, NULL, &swapchain));
        assert(bCreated && "Failed to Try to Create SwapChain!");

        auto bAssociation = SUCCEEDED(
            dxgiInstance->pDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER));
        assert(bAssociation && "Failed to Try to Associate SwapChain With Window!");

        auto bQueryChain3 = SUCCEEDED(swapchain->QueryInterface(IID_PPV_ARGS(&pSwapChain)));
        assert(bQueryChain3 && "Failed to Query IDXGISwapChain3 from Created SwapChain!");
    }
}