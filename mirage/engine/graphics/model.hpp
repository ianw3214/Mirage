#pragma once

#include "util/util.hpp"

#include "platform/opengl/glwrappers.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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
        , m_rotation(1.0, 0.0, 0.0, 0.0)
        , m_texture(nullptr)
    {
		// Do this to prevent copying in the vector so that destructors aren't accidentally called
		vbs.reserve(3);
	}

    ~RawModel()
    {
        delete m_texture;
    }

    // Scale getter/setters
    void SetScale(float scale) { m_scale = scale; }
    float GetScale() const { return m_scale; }

    // Position getter/setters
    void SetPosition(Vec3f position) { m_position = position; }
    void SetPosition(float x, float y, float z) { m_position = {x, y, z}; }
    Vec3f GetPosition() const { return m_position; }

    // Rotation getter/setters
    inline void SetRotation(float angle, glm::vec3 axis) {
        m_rotation = glm::fquat(1.0, 0.0, 0.0, 0.0);
        AddRotation(angle, axis);
    }
    inline void AddRotation(float angle, glm::vec3 axis) {
        m_rotation = glm::rotate(m_rotation, glm::radians(angle), axis);
    }
    void SetRotation(glm::fquat rotation) { m_rotation = rotation; }
    glm::fquat GetRotation() const { return m_rotation; }

    void SetTexture(std::string path)
    {
        if (m_texture) delete m_texture;
        m_texture = new Oasis::Texture(path);
    }
    Oasis::Texture * GetTexture() const { return m_texture; }

private:
    float m_scale;
    Vec3f m_position;
    glm::fquat m_rotation;

    Oasis::Texture * m_texture;
};

typedef Mirage::Reference<RawModel> ModelRef;