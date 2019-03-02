#pragma once

#ifdef PLATFORM_WINDOWS
    #ifdef BUID_DLL
        #define API __declspec(dllexport)
    #else
        #define API __declspec(dllimport)
    #endif
#else
    #define API
#endif