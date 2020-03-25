#pragma once

#include "model.hpp"

class Terrain
{
public:
    static constexpr float kSize = 10.f;
    static constexpr int kVertexCount = 128;

    Terrain(int x = 0, int y = 0);

    ModelRef GetModel() { return m_model; }
private:
    float m_x;
    float m_y;

    Mirage::Owned<RawModel> m_model;
    // TODO: Texture

    //////////////////////////////////////////////////////////////
    // Utility functions
    void GenerateTerrain();
};