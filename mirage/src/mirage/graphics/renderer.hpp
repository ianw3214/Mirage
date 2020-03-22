#pragma once

#include "objloader.hpp"

namespace Mirage
{
    // TODO: TEMPORARY - MOVE ELSEWHERE
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

    class MIRAGE_API Renderer
    {
    public:
        Renderer();
        
        void Clear(float r, float g, float b);

        void DrawQuad(float x, float y, float w, float h, const Colour& colour);
        void DrawModel(ModelRef model, const Colour& colour);
    private:
        struct Impl;
        Impl * m_impl;
    };
}