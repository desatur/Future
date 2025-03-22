#pragma once

#ifdef FUTURE_EXPORT
    #define FUTURE_API __declspec(dllexport)
#else
    #define FUTURE_API __declspec(dllimport)
#endif