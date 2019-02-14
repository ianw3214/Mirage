#pragma once

#include "platform/opengl/shader.hpp"
#include "graphics/rawModel.hpp"

// TODO: (Ian) Use custom lightweight string implementation
// TODO: (Ian) Use custom lightweight smart pointer implementation
// TODO: (Ian) Use custom map implementation w/ custom allocator
#include <string>
#include <memory>
#include <unordered_map>

// Typedefs for QoL
typedef const Shader& ShaderRef;
typedef const std::unique_ptr<Shader>& ShaderRefPtr;
typedef const RawModel& ModelRef;
typedef const std::unique_ptr<RawModel>& ModelRefPtr;

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    // Don't allow copy/move constructing
    ResourceManager(ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) = delete;

    ShaderRefPtr loadShader(std::string name, std::string vertex, std::string fragment);
    ShaderRefPtr getShader(std::string name);

    ModelRefPtr loadModel(std::string name, std::string path);
    ModelRefPtr getModel(std::string name);
    
private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<RawModel>> models;
};