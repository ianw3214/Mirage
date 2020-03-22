#pragma once

#include "objloader.hpp"

namespace Mirage
{
    class Renderer
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