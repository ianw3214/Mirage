#pragma once

#include <string>
#include <vector>

#include "opengl/glwrappers.hpp"

#include <sstream>
namespace Util {
	// String tokenizing utility function
	typedef std::vector<std::string> StrTokens;
	inline StrTokens split(const std::string& s, char delimiter = ' ', bool removeEmpty = false)
	{
		StrTokens tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			if (removeEmpty && token.size() == 0) continue;
			tokens.push_back(token);
		}
		return tokens;
	}
}

struct Vec2 {
    float x;
    float y;
};

struct Vec3 {
    float x;
    float y;
    float z;
};

class RawModel {
public:
	VertexArray * va;
	IndexBuffer * ib;

	// Keep track of VBOs in order to free them later
	VertexBuffer * vb_pos;
	VertexBuffer * vb_nrm;
	VertexBuffer * vb_tex;

	RawModel() {}
	RawModel(const std::string& path) {
		loadModel(path);
	}

	void loadModel(const std::string& path);

};