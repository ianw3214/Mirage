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