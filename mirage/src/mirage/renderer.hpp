#pragma once

namespace Mirage
{
    class Renderer
    {
    public:
        Renderer();
        
        void Clear(float r, float g, float b);
    private:
        struct Impl;
        Impl * m_impl;
    };
}