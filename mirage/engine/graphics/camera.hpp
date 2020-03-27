#pragma once

// TODO: Maybe put this in a graphicsToolbox folder, separate from base graphics

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    Camera() : m_cameraPos(), m_cameraTarget() {}
    ~Camera() {}

    void SetPosition(float x, float y, float z) { m_cameraPos = glm::vec3(x, y, z); }
    void SetPosition(Vec3f pos) { m_cameraPos = glm::vec3(pos.x, pos.y, pos.z); }
    void SetPosition(glm::vec3 pos) { m_cameraPos = pos; }
    void SetTarget(float x, float y, float z) { m_cameraTarget = glm::vec3(x, y, z); }
    void SetTarget(Vec3f pos) { m_cameraTarget = glm::vec3(pos.x, pos.y, pos.z); }
    void SetTarget(glm::vec3 pos) { m_cameraTarget = pos; }

    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(m_cameraPos, m_cameraTarget, glm::vec3(0.f, 1.f, 0.f));
    }

    glm::mat4 GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(45.f), 8.f / 6.f, 0.01f, 100.f);
    }
private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraTarget;
};