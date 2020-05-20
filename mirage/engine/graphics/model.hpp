#pragma once

#include "util/util.hpp"

#include "platform/opengl/glwrappers.hpp"

class RawModel {
public:
	VertexArray va;
	IndexBuffer ib;

	// Keep track of VBOs in order to free them later
	std::vector<VertexBuffer> vbs;

	RawModel(unsigned int * indices, unsigned int count) 
        : va()
        , ib(indices, count) 
        , m_scale(1.f)
        , m_position()
        , m_texture(nullptr)
    {
		// Do this to prevent copying in the vector so that destructors aren't accidentally called
		vbs.reserve(3);
	}

    ~RawModel()
    {
        delete m_texture;
    }

    void SetScale(float scale) { m_scale = scale; }
    float GetScale() const { return m_scale; }
    void SetPosition(Vec3f position) { m_position = position; }
    void SetPosition(float x, float y, float z) { m_position = {x, y, z}; }
    Vec3f GetPosition() const { return m_position; }
    void SetTexture(std::string path)
    {
        if (m_texture) delete m_texture;
        m_texture = new Oasis::Texture(path);
    }
    Oasis::Texture * GetTexture() const { return m_texture; }

private:
    float m_scale;
    Vec3f m_position;
    // TODO: Rotation

    Oasis::Texture * m_texture;
};

typedef Mirage::Reference<RawModel> ModelRef;