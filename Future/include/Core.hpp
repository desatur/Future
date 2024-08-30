#pragma once

#ifdef FE_BUILD_LIB
    #define FE_API __declspec(dllexport)
#else
    #define FE_API __declspec(dllimport)
#endif