#pragma once
#include "TexType.hpp"
#include <string>

namespace Future {
    class TexTypeHelpers {
        public:
            static std::string TexTypeToString(TexType type);
    };
}