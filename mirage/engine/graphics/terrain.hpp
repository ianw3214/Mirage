#pragma once

#include "model.hpp"

#include <vector>

class Terrain
{
public:
    static constexpr float kSize = 100.f;
    static constexpr int kVertexCount = 128;

    Terrain(int x = 0, int y = 0);

    ModelRef GetModel() { return m_model; }
    float GetHeightOfTerrain(float worldX, float worldY);
private:
    float m_x;
    float m_y;
    // Store the heights so we don't need to read the heightmap all the time
    // TODO: Can probably just use single dimension vector
    std::vector<std::vector<float>> m_heights;

    Mirage::Owned<RawModel> m_model;
    // TODO: Texture

    //////////////////////////////////////////////////////////////
    // Utility functions
    void GenerateTerrain();
    float GetHeight(int x, int z, unsigned char * localBuffer, int width, int height);
    Vec3f CalculateNormal(int x, int z, unsigned char * localBuffer, int width, int height);
};