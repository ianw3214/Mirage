#pragma once

#include "objloader.hpp"

namespace Mirage
{
    class Renderer
    {
    public:
        Renderer();
        
        void ClearColour(float r, float g, float b);
        void Clear();

        void DrawQuad(float x, float y, float w, float h, const Colour& colour = Mirage::Colours::RED);
        void DrawModel(ModelRef model, const Colour& colour = Mirage::Colours::RED);
    private:
        struct Impl;
        Impl * m_impl;
    };
}