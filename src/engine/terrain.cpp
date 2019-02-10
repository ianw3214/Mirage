#include "terrain.hpp"

Terrain::Terrain(float grid_x, float grid_z) {
    x = grid_x;
    z = grid_z;
    generateFlatTerrain();
}

Terrain::~Terrain() {
    // Cleanup resources
}

void Terrain::generateFlatTerrain() {
    // Clear the previous model in case it exists
    model.clear();
    int count = VERTEX_COUNT * VERTEX_COUNT;
    float * vertices = new float[count * 3];
    float * normals = new float[count * 3];
    float * textureCoords = new float[count * 2];
    unsigned int * indices = new unsigned int[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];
    int vertexPointer = 0;
    for (int i = 0; i < VERTEX_COUNT; ++i) {
        for (int j = 0; j < VERTEX_COUNT; ++j) {
            vertices[vertexPointer * 3] = (x + (static_cast<float>(j) / (static_cast<float>(VERTEX_COUNT) - 1.f))) * SIZE;
            vertices[vertexPointer * 3 + 1] = 0.f;
            vertices[vertexPointer * 3 + 2] = (z + (static_cast<float>(i) / (static_cast<float>(VERTEX_COUNT) - 1.f))) * SIZE;
            normals[vertexPointer * 3] = 0;
            normals[vertexPointer * 3 + 1] = 1;
            normals[vertexPointer * 3 + 2] = 0;
            textureCoords[vertexPointer * 2] = static_cast<float>(j) / (static_cast<float>(VERTEX_COUNT) - 1.f);
            textureCoords[vertexPointer * 2 + 1] = static_cast<float>(i) / (static_cast<float>(VERTEX_COUNT) - 1.f);
            vertexPointer++;
        }
    }
    // Temporary scale up of texture shit
    // TODO: (Ian) Don't do this
    for (int i = 0; i < count * 2; ++i) {
        textureCoords[i] *= 100.f;
    }
    int pointer = 0;
    for (int gz = 0; gz < VERTEX_COUNT - 1; ++gz) {
        for (int gx = 0; gx < VERTEX_COUNT - 1; ++gx) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    // Construct the model
    model.fromArrays(vertices, normals, textureCoords, indices, count, 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
}

const RawModel& Terrain::getModel() const {
    return model;
}