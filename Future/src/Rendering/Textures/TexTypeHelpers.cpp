#include "TexTypeHelpers.hpp"

namespace Future
{
    std::string TexTypeHelpers::TexTypeToString(TexType type) {
        switch (type) {
            case TexType::UNDEFINED: return "UNDEFINED";
            case TexType::DIFFUSE: return "DIFFUSE";
            case TexType::SPECULAR: return "SPECULAR";
            case TexType::NORMAL: return "NORMAL";
            default: return "UNKNOWN";
        }
    }
}
