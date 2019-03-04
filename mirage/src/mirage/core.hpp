#pragma once

#ifdef PLATFORM_WINDOWS
    #ifdef BUID_DLL
        #define MIRAGE_API __declspec(dllexport)
    #else
        #define MIRAGE_API __declspec(dllimport)
    #endif
#else
    #define MIRAGE_API
#endif