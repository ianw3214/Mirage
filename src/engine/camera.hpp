#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#define DEFAULT_CAMERA_SPEED    0.1f
#define DEFAULT_YAW             0.0f
#define DEFUALT_PITCH           0.0f
#define DEFAULT_FOV             30.f

enum class CameraDirection {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {

public:
    Camera(bool defaultMovement = true,
        float speed = DEFAULT_CAMERA_SPEED, 
        float yaw =DEFAULT_YAW, 
        float pitch =DEFUALT_PITCH, 
        float fov = DEFAULT_FOV);
    ~Camera();

    // Basic functions of the camera
    void onEvent(const SDL_Event& e);
    void update();

    // Other functions to interact with camera properties
    void setPosition(glm::vec3 pos);
    void setPosition(float x, float y, float z);
    void setDirection(glm::vec3 dir);
    void setDirection(float x, float y, float z);
    void setDefaultMovement(bool defaultMovement);
    void move(CameraDirection dir, float distance);

    // Getter functions of the camera
    glm::mat4 getViewMatrix() const;
    float getFov() const;
private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;

    float m_cameraSpeed;
    float m_yaw, m_pitch;
    // TODO: (Ian) Move FOV out of camera class
    float m_fov;

    bool m_defaultMovement;
    bool m_key_front;
    bool m_key_back;
    bool m_key_left;
    bool m_key_right;
    bool m_key_up;
    bool m_key_down;
private:
    // Helper functions
    void calculateCameraFront();
};