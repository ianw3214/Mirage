#include "resource.hpp"

const std::unique_ptr<Shader> NULL_SHADER = nullptr;
const std::unique_ptr<RawModel> NULL_MODEL = nullptr;

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
	// Make sure the shader exists before returning it
	if (shaders.find(name) == shaders.end()) {
		return NULL_SHADER;
	}
	return shaders[name];
}

ModelRefPtr ResourceManager::loadModel(std::string name, std::string path) {
	models.insert({name, std::make_unique<RawModel>(path)});
	return models[name];
}

ModelRefPtr ResourceManager::getModel(std::string name) {
	// Make sure the model exists before returning it
	if (models.find(name) == models.end()) {
		return NULL_MODEL;
	}
	return models[name];
}