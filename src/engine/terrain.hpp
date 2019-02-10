#pragma once

#include "graphics/rawModel.hpp"

class Terrain {

// Class constants
public:
    static constexpr float SIZE = 800.f;
    static constexpr int VERTEX_COUNT = 128;
public:
    Terrain(float grid_x, float grid_z);
    ~Terrain();

    void generateFlatTerrain();

    const RawModel& getModel() const;
private:
    float x;
    float z;
    RawModel model;
    // TODO: (Ian) Implement texturing
};