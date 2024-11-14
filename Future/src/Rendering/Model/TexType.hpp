#ifndef TEXTYPE_HPP
#define TEXTYPE_HPP

#include <cstdint>

enum class TexType : std::uint8_t {
    UNDEFINED = 0,
    DIFFUSE = 1,
    SPECULAR = 2,
    NORMAL = 3
};

#endif