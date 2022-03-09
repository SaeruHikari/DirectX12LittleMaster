#pragma once
#include <type_traits>

class LittleFactory
{
public:
    template <typename T, typename... Args>
    inline static T* Create(Args&&... args)
    {
        auto res = new T();
        if (res->Initialize(std::forward<Args>(args)...))
            return res;
        else
            return nullptr;
    }
    template <typename T>
    inline static bool Destroy(T* object)
    {
        if (object->Destroy())
        {
            delete object;
            return true;
        }
        return false;
    }
};