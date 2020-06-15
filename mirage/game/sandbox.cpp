#include "engine.hpp"

#include "graphics/graphics.hpp"
#include "GL/glew.h"

// TODO: Custom keycodes so no need to include SDL
#include <SDL2/SDL.h>

#ifdef MIRAGE_EDITOR
#include <imgui-docking/imgui.h>
#endif

constexpr int ticksPerDay = 30000;

class SandboxState : public Mirage::State {
public:
    void Init() {
        Mirage::ApplicationManager::GetCamera()->SetPosition(0.f, 3.f, 5.f);
        loader.loadModel("res/test.obj");

        terrain1 = new Terrain(0, 0);
        terrain2 = new Terrain(0, -1);

        m_playerPos = Vec3f{0.f, 0.f, 0.f};
        m_angleH = 0.f;
        m_angleV = 0.1f;
        m_movingCamera = false;
        m_cameraMoveStartAngleH = 0.f;
        m_cameraMoveStartAngleV = 0.1f;
        m_cameraMoveStartX = 0;
        m_cameraMoveStartY = 0;

        m_timeTick = 0;
    }
    void Shutdown() {

    }
    void Update() {
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_W))
        {
            m_playerPos.x -= std::sin(m_angleH) * 0.01f;
            m_playerPos.z -= std::cos(m_angleH) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_S))
        {
            m_playerPos.x += std::sin(m_angleH) * 0.01f;
            m_playerPos.z += std::cos(m_angleH) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_D))
        {
            m_playerPos.x += std::sin(m_angleH + 1.57079632679f) * 0.01f;
            m_playerPos.z += std::cos(m_angleH + 1.57079632679f) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_A))
        {
            m_playerPos.x += std::sin(m_angleH - 1.57079632679f) * 0.01f;
            m_playerPos.z += std::cos(m_angleH - 1.57079632679f) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->LeftMouseClicked())
        {
            m_movingCamera = true;
            m_cameraMoveStartAngleH = m_angleH;
            m_cameraMoveStartAngleV = m_angleV;
            m_cameraMoveStartX = Mirage::ApplicationManager::GetInput()->GetMouseX();
            m_cameraMoveStartY = Mirage::ApplicationManager::GetInput()->GetMouseY();
        }
        if (Mirage::ApplicationManager::GetInput()->LeftMouseReleased())
        {
            m_movingCamera = false;
        }

        if (m_movingCamera)
        {
            constexpr float sensitivity = 0.005f;
            float offsetX = m_cameraMoveStartX - Mirage::ApplicationManager::GetInput()->GetMouseX();
            m_angleH = m_cameraMoveStartAngleH + offsetX * sensitivity;
            float offsetY = m_cameraMoveStartY - Mirage::ApplicationManager::GetInput()->GetMouseY();
            m_angleV = m_cameraMoveStartAngleV - offsetY * sensitivity;
            if (m_angleV > 1.57f) m_angleV = 1.57f;
            if (m_angleV < -1.57f) m_angleV = -1.57f;
        }

        {   // Update the camera
            Vec3f cameraPos = m_playerPos;
            cameraPos.x += (std::sin(m_angleH) * (std::cos(m_angleV))) * 10.f;
            cameraPos.y += std::sin(m_angleV) * 10.f;    // Always 3m above ground
            cameraPos.z += (std::cos(m_angleH) * (std::cos(m_angleV))) * 10.f;
            Mirage::ApplicationManager::GetCamera()->SetPosition(cameraPos);
            Mirage::ApplicationManager::GetCamera()->SetTarget(m_playerPos);
        }

        ModelRef model = loader.getModel("res/test.obj");
        model->SetPosition(m_playerPos.x, m_playerPos.y + 1.f, m_playerPos.z);
        model->SetScale(1.f);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(model);

        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain1->GetModel());
        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain2->GetModel());

        // Maybe use a curve instead of direct lerp
        // Update clear color for day/night time
        float blue = static_cast<float>(std::abs(m_timeTick * 2 - ticksPerDay)) / static_cast<float>(ticksPerDay);
        Mirage::ApplicationManager::GetRenderer()->ClearColour(0.f, blue * 2.f / 3.f, blue);
        if (++m_timeTick > ticksPerDay)
        {
            m_timeTick = 0;
        }
        #ifdef MIRAGE_EDITOR
        {
            ImGui::Begin("Game");
            ImGui::SliderInt("time of day", &m_timeTick, 0, ticksPerDay);
            ImGui::End();
        }
        #endif

        {   // Raycasting? :o
            float mouseX = Mirage::ApplicationManager::GetInput()->GetMouseX();
            float mouseY = Mirage::ApplicationManager::GetInput()->GetMouseY();
            // Normalize x/y coordinates
            // TODO: Get window width/height from engine
            mouseX = 2.f * mouseX / 1280.f - 1.f;
            // In openGL y is positive in the up direction so it must be reversed
            mouseY = -(2.f * mouseY / 720.f - 1.f);
            glm::vec4 clipCoords(mouseX, mouseY, -1.f, 1.f);
            // Clip coordinates to eye space coordinates
            glm::vec4 eyeCoords = glm::inverse(Mirage::ApplicationManager::GetCamera()->GetProjectionMatrix()) * clipCoords;
            eyeCoords.z = -1.f;
            eyeCoords.w = 0.f;
            // Eye space coords to world coords
            glm::vec4 worldCoords = glm::inverse(Mirage::ApplicationManager::GetCamera()->GetViewMatrix()) * eyeCoords;
            glm::vec3 ray = glm::normalize(glm::vec3(worldCoords));

            // Actually convert the ray to terrain intersection point
            auto fGetPointOnRay = [](glm::vec3 ray, float distance){
                glm::vec3 cam_pos = Mirage::ApplicationManager::GetCamera()->GetPosition();
                glm::vec3 scaled_ray = ray * distance;
                return cam_pos + scaled_ray;
            };

            auto fIsUnderground = [&](glm::vec3 target){
                // Just test 1 terrain for now
                float height = terrain1->GetHeightOfTerrain(target.x, target.z);
                return target.y < height;
            };

            auto fIntersectionInRange = [&fGetPointOnRay, &fIsUnderground](float start, float finish, glm::vec3 ray){
                glm::vec3 startPoint = fGetPointOnRay(ray, start);
                glm::vec3 endPoint = fGetPointOnRay(ray, finish);
                return !fIsUnderground(startPoint) && fIsUnderground(endPoint);
            };

            std::function<glm::vec3(int,float, float, glm::vec3)> fBinarySearch;
            fBinarySearch = [&fGetPointOnRay, &fIntersectionInRange, &fBinarySearch](int count, float start, float finish, glm::vec3 ray){
                float half = start + ((finish - start) / 2.f);
                if (count >= 200)   // This is the max recursion count
                {
                    return fGetPointOnRay(ray, half);
                }
                if (fIntersectionInRange(start, half, ray))
                {
                    return fBinarySearch(count + 1, start, half, ray);
                }
                else
                {
                    return fBinarySearch(count + 1, half, finish, ray);
                }
            };

            glm::vec3 point = fBinarySearch(0, 0.f, 600.f, ray);

            ModelRef model = loader.getModel("res/test.obj");
            model->SetPosition(point.x, point.y, point.z);
            model->SetScale(0.3f);
            Mirage::ApplicationManager::GetRenderer()->DrawModel(model);

            #ifdef MIRAGE_EDITOR
            {
                glm::vec3 cam_pos = Mirage::ApplicationManager::GetCamera()->GetPosition();
                
                ImGui::Begin("Ray test");
                ImGui::Text("Mouse pos");
                ImGui::Text("%f, %f", mouseX, mouseY);
                ImGui::Text("Camera pos");
                ImGui::Text("%f, %f, %f", cam_pos.x, cam_pos.y, cam_pos.z);
                ImGui::Text("Ray");
                ImGui::Text("%f, %f, %f", ray.x, ray.y, ray.z);
                ImGui::Text("Terrain height");
                ImGui::Text("%f", terrain1->GetHeightOfTerrain(m_playerPos.x, m_playerPos.z));
                ImGui::Text("Ray Hit");
                ImGui::Text("%f, %f, %f", point.x, point.y, point.z);
                ImGui::End();
            }
            #endif
        }
    }
private:
    OBJLoader loader;
    Mirage::Owned<Terrain> terrain1;
    Mirage::Owned<Terrain> terrain2;

    // Camera adjusting code
    Vec3f m_playerPos;
    float m_angleH;
    float m_angleV;
    bool m_movingCamera;
    float m_cameraMoveStartAngleH;
    float m_cameraMoveStartAngleV;
    float m_cameraMoveStartX;
    float m_cameraMoveStartY;

    // Day/night cycle cause why not
    int m_timeTick;
};

Mirage::WindowConfig Mirage::GetConfiguration()
{
    WindowConfig config("SANDBOX", 1280, 720);
    config.initialState = []() -> Mirage::State* { return new SandboxState(); };
    return config;
}