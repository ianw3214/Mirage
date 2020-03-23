#pragma once

#include "util/util.hpp"
#include "model.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class RawModel;

// TODO: More global access to obj loader (don't want to instantiate all the time)
class OBJLoader {

public:

	OBJLoader();
	~OBJLoader();

	static void loadModel(std::string path);
	static void loadModel(std::string name, std::string path);
	static ModelRef getModel(std::string name);
    
private:

	static void processVertex(
		const std::vector<std::string> vertex, 
		std::vector<unsigned int>& indices, 
		const std::vector<Vec2f> textures, 
		const std::vector<Vec3f> normals, 
		float textureArray[], 
		float normalsArray[]);

	static std::unordered_map<std::string, Mirage::Owned<RawModel>> models;

};