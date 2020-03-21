#include "OBJloader.hpp"

#include <fstream>

// TODO: Put this somewhere better
// String tokenizing utility function
#include <sstream>
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

std::unordered_map<std::string, std::unique_ptr<RawModel>> OBJLoader::models;

OBJLoader::OBJLoader() {

}

OBJLoader::~OBJLoader() {

}

// Load the model with it's own path as the name if no name was passed
void OBJLoader::loadModel(std::string path) {
	loadModel(path, path);
	return;
}

void OBJLoader::loadModel(std::string name, std::string path) {

	std::ifstream model_file(path);
	if (!model_file) {
		// TODO: error handling
	}

	// TODO: error handling for when file layout wrong
	//	- possibly using exceptions
	std::string line;
	std::vector<Vec3f> vertices;
	std::vector<Vec2f> textures;
	std::vector<Vec3f> normals;
	std::vector<unsigned int> indices;
	float * verticesArray = nullptr;
	float * normalsArray = nullptr;
	float * textureArray  = nullptr;
	bool texturesFound = false;
	while (std::getline(model_file, line)) {
		std::vector<std::string> tokens = split(line);
		if (tokens[0] == "v") {			// VERTEX POSITION
			Vec3f pos = Vec3f{std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])};
			vertices.push_back(pos);
		}
		if (tokens[0] == "vn") {		// VERTEX NORMAL
			Vec3f normal = Vec3f{std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])};
			normals.push_back(normal);
		}
		if (tokens[0] == "vt") {		// VERTEX TEXTURE
			texturesFound = true;
			Vec2f texture = Vec2f{std::stof(tokens[1]), std::stof(tokens[2])};
			textures.push_back(texture);
		}
		if (tokens[0] == "f") {			// FACE
			if (!verticesArray || !textureArray || !normalsArray) {
				verticesArray = new float[vertices.size() * 3];
				normalsArray = new float[vertices.size() * 3];
				textureArray  = new float[vertices.size() * 2];
			}
			std::vector<std::string> vertex1 = split(tokens[1], '/');
			std::vector<std::string> vertex2 = split(tokens[2], '/');
			std::vector<std::string> vertex3 = split(tokens[3], '/');

			processVertex(vertex1, indices, textures, normals, textureArray, normalsArray);
			processVertex(vertex2, indices, textures, normals, textureArray, normalsArray);
			processVertex(vertex3, indices, textures, normals, textureArray, normalsArray);
		}
	}

	unsigned int * indicesArray = indices.data();
	int indexPtr = 0;
	for (Vec3f vertex : vertices) {
		verticesArray[indexPtr++] = vertex.x;
		verticesArray[indexPtr++] = vertex.y;
		verticesArray[indexPtr++] = vertex.z;
	}

	std::unique_ptr<RawModel> model = std::make_unique<RawModel>(&(indices[0]), indices.size());
    // TODO: This can be setup to use the same buffer layout for all 3
	{	// SETUP VERTEX POSITIONS BUFFER
		model->vbs.emplace_back(verticesArray, sizeof(float) * vertices.size() * 3);
		VertexBuffer& vb_pos = model->vbs[0];
		VertexBufferLayout vb_pos_layout;
		vb_pos_layout.pushFloat(3);
		model->va.addBuffer(vb_pos, vb_pos_layout, 0);
	}
	{	// SETUP VERTEX NORMALS BUFFER
		model->vbs.emplace_back(verticesArray, sizeof(float) * vertices.size() * 3);
		VertexBuffer& vb_nrm = model->vbs[1];
		VertexBufferLayout vb_nrm_layout;
		vb_nrm_layout.pushFloat(3);
		model->va.addBuffer(vb_nrm, vb_nrm_layout, 1);
	}
	if (texturesFound)
	{	// SETUP VERTEX TEXTURES BUFFER
		model->vbs.emplace_back(verticesArray, sizeof(float) * vertices.size() * 2);
		VertexBuffer& vb_tex = model->vbs[2];
		VertexBufferLayout vb_tex_layout;
		vb_tex_layout.pushFloat(2);
		model->va.addBuffer(vb_tex, vb_tex_layout, 2);
	}
	models[name] = std::move(model);
	return;
}

ModelRef OBJLoader::getModel(std::string name) {
	// Try to load the model with the name as the file path if it doesn't exist yet
	if (models.find(name) == models.end()) {
		loadModel(name);
	}
	return models[name];
}

void OBJLoader::processVertex(
	const std::vector<std::string> vertex, 
	std::vector<unsigned int>& indices,
	const std::vector<Vec2f> textures, 
	const std::vector<Vec3f> normals, 
	float textureArray[], 
	float normalsArray[]) 
{
	int currPointer = std::stoi(vertex[0]) - 1;
	indices.push_back(currPointer);
	if (vertex[1].size() > 0) {
		Vec2f currTex = textures[std::stoi(vertex[1]) - 1];
		textureArray[currPointer * 2 + 0] = currTex.x;
		textureArray[currPointer * 2 + 1] = 1.f - currTex.y;
	}
	if (vertex[2].size() > 0) {
		Vec3f currNorm = normals[std::stoi(vertex[2]) - 1];
		normalsArray[currPointer * 3 + 0] = currNorm.x;
		normalsArray[currPointer * 3 + 1] = currNorm.y;
		normalsArray[currPointer * 3 + 2] = currNorm.z;
	}
}