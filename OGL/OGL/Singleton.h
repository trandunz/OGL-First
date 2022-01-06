#pragma once
#include "NumptyBehavior.h"


class Singleton :
    public NumptyBehavior
{
public:
    Singleton(const Singleton&) = delete;
    
    static Singleton& Get()
    {
        static Singleton s_Instance;
        return s_Instance;
    }
private:
    Singleton();

};
typedef Singleton&(*get)();