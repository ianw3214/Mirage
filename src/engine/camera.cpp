#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

const glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

Camera::Camera(bool defaultMovement, float speed, float yaw, float pitch, float fov) {
    m_defaultMovement = defaultMovement;
    m_cameraSpeed = speed;
    m_yaw = yaw;
    m_pitch = pitch;
    m_fov = fov;
}

Camera::~Camera() {

}

void Camera::onEvent(const SDL_Event& e) {
    if (m_defaultMovement) {
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_w) {
                m_key_front = true;
            }
            if (e.key.keysym.sym == SDLK_s) {
                m_key_back = true;
            }
            if (e.key.keysym.sym == SDLK_a) {
                m_key_left = true;
            }
            if (e.key.keysym.sym == SDLK_d) {
                m_key_right = true;
            }
            if (e.key.keysym.sym == SDLK_LSHIFT) {
                m_key_up = true;
            }
        }
        if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_w) {
                m_key_front = false;
            }
            if (e.key.keysym.sym == SDLK_s) {
                m_key_back = false;
            }
            if (e.key.keysym.sym == SDLK_a) {
                m_key_left = false;
            }
            if (e.key.keysym.sym == SDLK_d) {
                m_key_right = false;
            }
            if (e.key.keysym.sym == SDLK_LSHIFT) {
                m_key_up = false;
            }
        }
        if (e.type == SDL_MOUSEMOTION) {
            float sensitivity = 0.05f;
            float xoffset = static_cast<float>(e.motion.xrel) * sensitivity;
            float yoffset = static_cast<float>(e.motion.yrel) * sensitivity;
            m_yaw += xoffset;
            m_pitch -= yoffset;
            if (m_pitch > 89.f) m_pitch = 89.f;
            if (m_pitch < -89.f) m_pitch = -89.f;
        }
        if (e.type == SDL_MOUSEWHEEL) {
            if (m_fov >= 1.f && m_fov < 45.f) {
                m_fov -= e.wheel.y;
            }
            if (m_fov <= 1.f) m_fov = 1.f;
            if (m_fov >= 45.f) m_fov = 45.f;
        }
    }
}

void Camera::update() {
    // Update camera position based on keys
    if (m_key_front)    move(CameraDirection::FRONT,    m_cameraSpeed);
    if (m_key_back)     move(CameraDirection::BACK,     m_cameraSpeed);
    if (m_key_left)     move(CameraDirection::LEFT,     m_cameraSpeed);
    if (m_key_right)    move(CameraDirection::RIGHT,    m_cameraSpeed);
    if (m_key_up)       move(CameraDirection::UP,       m_cameraSpeed);
    if (m_key_down)     move(CameraDirection::DOWN,     m_cameraSpeed);
    // Update the camera front vector to reflect any event updates
    calculateCameraFront();
}

void Camera::setPosition(glm::vec3 pos) {
    m_cameraPos = pos;
}

void Camera::setPosition(float x, float y, float z) {
    m_cameraPos = glm::vec3(x, y, z);
}

void Camera::setDirection(glm::vec3 dir) {
    m_cameraFront = dir;
}

void Camera::setDirection(float x, float y, float z) {
    m_cameraFront = glm::vec3(x, y, z);
}


void Camera::setDefaultMovement(bool defaultMovement) {
    m_defaultMovement = defaultMovement;
}

void Camera::move(CameraDirection dir, float distance) {
    if (dir == CameraDirection::FRONT)  m_cameraPos += distance * m_cameraFront;
    if (dir == CameraDirection::BACK)   m_cameraPos -= distance * m_cameraFront;
    if (dir == CameraDirection::LEFT)   m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, up)) * distance;
    if (dir == CameraDirection::RIGHT)  m_cameraPos += glm::normalize(glm::cross(m_cameraFront, up)) * distance;
    if (dir == CameraDirection::UP)     m_cameraPos += distance * up;
    if (dir == CameraDirection::DOWN)   m_cameraPos -= distance * up;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, up);
}

float Camera::getFov() const {
    return m_fov;
}

void Camera::calculateCameraFront() {
    glm::vec3 front;
    front.x = std::cos(glm::radians(m_pitch)) * std::cos(glm::radians(m_yaw));
    front.y = std::sin(glm::radians(m_pitch));
    front.z = std::cos(glm::radians(m_pitch)) * std::sin(glm::radians(m_yaw));
    m_cameraFront = glm::normalize(front);
}