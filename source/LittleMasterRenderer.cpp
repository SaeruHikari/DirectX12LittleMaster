#include "gfx/gfx_objects.h"

class LittleRendererWindow final : public LittleGFXWindow
{
public:
    void Run() override
    {
        MSG msg = { 0 };
        while (msg.message != WM_QUIT)
        {
            // 处理系统的消息
            if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            // 在空闲时进行我们自己的逻辑
            else
            {
                // 暂时什么都不做
                // Sleep 1~2ms 来避免整个线程被while抢占
                Sleep(1);
            }
        }
        // 如果收到了WM_QUIT消息，我们直接退出此函数
        return;
    }
};

int main(void)
{
    // 创建并初始化实例
    auto instance = LittleFactory::Create<LittleGFXInstance>(true);
    auto device = LittleFactory::Create<LittleGFXDevice>(instance->GetAdapter(0));
    // 创建并初始化窗口类
    auto window = LittleFactory::Create<LittleRendererWindow>(L"LittleMaster", device, true);
    // 运行窗口类的循环
    window->Run();
    // 现在窗口已经关闭，我们清理窗口类
    LittleFactory::Destroy(window);
    // 清理实例
    LittleFactory::Destroy(device);
    LittleFactory::Destroy(instance);
    return 0;
}