#include "resource.hpp"

const std::unique_ptr<Shader> NULL_SHADER = nullptr;

ResourceManager::ResourceManager() {
    // Init shit here...
}

ResourceManager::~ResourceManager() {
    // Shutdown shit here...
}

ShaderRefPtr ResourceManager::loadShader(std::string name, std::string vertex, std::string fragment) {
	shaders.insert({name, std::make_unique<Shader>(vertex, fragment)});
	return shaders[name];
}

ShaderRefPtr ResourceManager::getShader(std::string name) {
    // Try to load the model with the name as the file path if it doesn't exist yet
	if (shaders.find(name) == shaders.end()) {
		return NULL_SHADER;
	}
	return shaders[name];
}