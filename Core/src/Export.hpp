#pragma once

#ifdef FUTURE_EXPORT
    #ifdef _MSC_VER
        #define FUTURE_API __declspec(dllexport)
    #else
        #define FUTURE_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define FUTURE_API __declspec(dllimport)
    #else
        #define FUTURE_API
    #endif
#endif
