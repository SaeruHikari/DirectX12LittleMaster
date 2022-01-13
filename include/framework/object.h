#pragma once

class LittleObject
{
public:
    LittleObject() = default;
    ~LittleObject() = default;
    virtual bool Initialize() = 0;
    virtual bool Destroy() = 0;
};

class LittleFactory
{
public:
    template<typename T, typename... Args>
    inline static T* Create(Args&&... args) {
        auto res = new T(args...);
        if(res->Initialize()) return res;
        else return nullptr;
    }
    template<typename T>
    inline static bool Destroy(T* object) {
        if(object->Destroy())
        {
            delete object;
            return true;
        }
        return false;
    }
};