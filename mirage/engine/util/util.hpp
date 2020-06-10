#pragma once

#include <glm/glm.hpp>

#include "pointer.hpp"

#define MIRAGE_TRAP(cond) if(!(cond)) *((unsigned int*)0) = 0xDEAD;

struct Vec2f
{
    float x;
    float y;

    glm::vec2 Get() const
    {
        return glm::vec2(x, y);
    }
};

struct Vec3f 
{
    float x;
    float y;
    float z;

    glm::vec3 Get() const
    {
        return glm::vec3(x, y, z);
    }
};

struct Vec4f 
{
    float x;
    float y;
    float z;
    float w;

    glm::vec4 Get() const
    {
        return glm::vec4(x, y, z, w);
    }
};

namespace Mirage
{
    struct Colour
    {
        float r;
        float g;
        float b;
    };

    namespace Colours
    {
        const static Colour WHITE = Colour{1.f, 1.f, 1.f};
        const static Colour BLACK = Colour{0.f, 0.f, 0.f};
        const static Colour RED = Colour{1.f, 0.f, 0.f};
        const static Colour GREEN = Colour{0.f, 1.f, 0.f};
        const static Colour BLUE = Colour{0.f, 0.f, 1.f};
    }
}

// String tokenizing utility function
#include <vector>
#include <string>
#include <sstream>
typedef std::vector<std::string> StrTokens;
inline StrTokens split(const std::string& s, char delimiter = ' ', bool removeEmpty = false)
{
    StrTokens tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        if (removeEmpty && token.size() == 0) continue;
        tokens.push_back(token);
    }
    return tokens;
}