#ifndef LOG_HPP
#define LOG_HPP

#include <memory>
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Future {
    class FE_API Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

// Macros
#define FE_CORE_ERROR(...) Future::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FE_CORE_WARN(...) Future::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FE_CORE_INFO(...) Future::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FE_CORE_TRACE(...) Future::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FE_CORE_DEBUG(...) Future::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define FE_CORE_FATAL(...) Future::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define FE_ERROR(...) Future::Log::GetClientLogger()->error(__VA_ARGS__)
#define FE_WARN(...) Future::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FE_INFO(...) Future::Log::GetClientLogger()->info(__VA_ARGS__)
#define FE_TRACE(...) Future::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FE_DEBUG(...) Future::Log::GetClientLogger()->debug(__VA_ARGS__)
#define FE_FATAL(...) Future::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif //LOG_HPP
