#pragma once
#include <assert.h>
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
#include "windows.h"

#ifndef SAFE_RELEASE
    #define SAFE_RELEASE(p_var) \
        if (p_var)              \
        {                       \
            p_var->Release();   \
            p_var = NULL;       \
        }
#endif

#pragma warning (disable:4819)