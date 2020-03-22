#pragma once

#include "core.hpp"
#include "util/util.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "platform/opengl/glwrappers.hpp"

// TODO: Move this code somewhere else to make it shared
class RawModel {
public:
	VertexArray va;
	IndexBuffer ib;

	// Keep track of VBOs in order to free them later
	std::vector<VertexBuffer> vbs;

	RawModel(unsigned int * indices, unsigned int count) : va(), ib(indices, count) {
		// Do this to prevent copying in the vector so that destructors aren't accidentally called
		vbs.reserve(3);
	}
};

typedef const std::unique_ptr<RawModel>& ModelRef;


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

	static std::unordered_map<std::string, std::unique_ptr<RawModel>> models;

};