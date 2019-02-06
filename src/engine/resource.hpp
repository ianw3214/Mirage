#pragma once

#include "platform/opengl/shader.hpp"

// TODO: (Ian) Use custom lightweight string implementation
// TODO: (Ian) Use custom lightweight smart pointer implementation
// TODO: (Ian) Use custom map implementation w/ custom allocator
#include <string>
#include <memory>
#include <unordered_map>

typedef const Shader& ShaderRef;
typedef const std::unique_ptr<Shader>& ShaderRefPtr;

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    // Don't allow copy/move constructing
    ResourceManager(ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) = delete;

    ShaderRefPtr loadShader(std::string name, std::string vertex, std::string fragment);
    ShaderRefPtr getShader(std::string name);
    
private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};