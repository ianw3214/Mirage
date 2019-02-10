#include "rawModel.hpp"

#include <fstream>

RawModel::~RawModel() {
	if(va) delete va;
	if(ib) delete ib;
	if(vb_pos) delete vb_pos;
	if(vb_nrm) delete vb_nrm;
	if(vb_tex) delete vb_tex;
}

void processVertex(
	const std::vector<std::string> vertex, 
	std::vector<unsigned int>& indices,
	const std::vector<Vec2> textures, 
	const std::vector<Vec3> normals, 
	float textureArray[], 
	float normalsArray[]) 
{
	int currPointer = std::stoi(vertex[0]) - 1;
	indices.push_back(currPointer);
	if (vertex[1].size() > 0) {
		Vec2 currTex = textures[std::stoi(vertex[1]) - 1];
		textureArray[currPointer * 2 + 0] = currTex.x;
		textureArray[currPointer * 2 + 1] = 1.f - currTex.y;
	}
	if (vertex[2].size() > 0) {
		Vec3 currNorm = normals[std::stoi(vertex[2]) - 1];
		normalsArray[currPointer * 3 + 0] = currNorm.x;
		normalsArray[currPointer * 3 + 1] = currNorm.y;
		normalsArray[currPointer * 3 + 2] = currNorm.z;
	}
}

void RawModel::clear() {
	if (va) delete va;
	if (ib) delete ib;
	if (vb_pos) delete vb_pos;
	if (vb_nrm) delete vb_nrm;
	if (vb_tex) delete vb_tex;
}

void RawModel::loadModel(const std::string& path) {
	
	std::ifstream model_file(path);
	if (!model_file) {
		vb_pos = nullptr;
		vb_nrm = nullptr;
		vb_tex = nullptr;
		return;
	}

	std::string line;
	std::vector<Vec3> vertices;
	std::vector<Vec2> textures;
	std::vector<Vec3> normals;
	std::vector<unsigned int> indices;
	float * verticesArray = nullptr;
	float * normalsArray = nullptr;
	float * textureArray  = nullptr;
	bool texturesFound = false;
	while (std::getline(model_file, line)) {
		std::vector<std::string> tokens = Util::split(line);
		if (tokens[0] == "v") {			// VERTEX POSITION
			Vec3 pos = Vec3{std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])};
			vertices.push_back(pos);
		}
		if (tokens[0] == "vn") {		// VERTEX NORMAL
			Vec3 normal = Vec3{std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])};
			normals.push_back(normal);
		}
		if (tokens[0] == "vt") {		// VERTEX TEXTURE
			texturesFound = true;
			Vec2 texture = Vec2{std::stof(tokens[1]), std::stof(tokens[2])};
			textures.push_back(texture);
		}
		if (tokens[0] == "f") {			// FACE
			if (!verticesArray || !textureArray || !normalsArray) {
				verticesArray = new float[vertices.size() * 3];
				normalsArray = new float[vertices.size() * 3];
				textureArray  = new float[vertices.size() * 2];
			}
			std::vector<std::string> vertex1 = Util::split(tokens[1], '/');
			std::vector<std::string> vertex2 = Util::split(tokens[2], '/');
			std::vector<std::string> vertex3 = Util::split(tokens[3], '/');

			processVertex(vertex1, indices, textures, normals, textureArray, normalsArray);
			processVertex(vertex2, indices, textures, normals, textureArray, normalsArray);
			processVertex(vertex3, indices, textures, normals, textureArray, normalsArray);
		}
	}

	unsigned int * indicesArray = indices.data();
	int indexPtr = 0;
	for (Vec3 vertex : vertices) {
		verticesArray[indexPtr++] = vertex.x;
		verticesArray[indexPtr++] = vertex.y;
		verticesArray[indexPtr++] = vertex.z;
	}

	va = new VertexArray();
	ib = new IndexBuffer(&(indices[0]), indices.size());
	{	// SETUP VERTEX POSITIONS BUFFER
		vb_pos = new VertexBuffer(verticesArray, sizeof(float) * vertices.size() * 3);
		VertexBufferLayout vb_pos_layout;
		vb_pos_layout.push_float(3);
		va->addBuffer(*vb_pos, vb_pos_layout, 0);
	}
	{	// SETUP VERTEX NORMALS BUFFER
		vb_nrm = new VertexBuffer(normalsArray, sizeof(float) * vertices.size() * 3);
		VertexBufferLayout vb_nrm_layout;
		vb_nrm_layout.push_float(3);
		va->addBuffer(*vb_nrm, vb_nrm_layout, 1);
	}
	if (texturesFound)
	{	// SETUP VERTEX TEXTURES BUFFER
		vb_tex = new VertexBuffer(textureArray, sizeof(float) * vertices.size() * 2);
		VertexBufferLayout vb_tex_layout;
		vb_tex_layout.push_float(2);
		va->addBuffer(*vb_tex, vb_tex_layout, 2);
	}
}

void RawModel::fromArrays(const float * vertices, 
	const float * normals, 
	const float * texCoords, 
	const unsigned int * indices,
	unsigned int num_vertices,
	unsigned int num_indices) 
{
	clear();
	va = new VertexArray();
	ib = new IndexBuffer(&(indices[0]), num_indices);
	{	// SETUP VERTEX POSITIONS BUFFER
		vb_pos = new VertexBuffer(vertices, sizeof(float) * num_vertices * 3);
		VertexBufferLayout vb_pos_layout;
		vb_pos_layout.push_float(3);
		va->addBuffer(*vb_pos, vb_pos_layout, 0);
	}
	{	// SETUP VERTEX NORMALS BUFFER
		vb_nrm = new VertexBuffer(normals, sizeof(float) * num_vertices * 3);
		VertexBufferLayout vb_nrm_layout;
		vb_nrm_layout.push_float(3);
		va->addBuffer(*vb_nrm, vb_nrm_layout, 1);
	}
	{	// SETUP VERTEX TEXTURES BUFFER
		vb_tex = new VertexBuffer(texCoords, sizeof(float) * num_vertices * 2);
		VertexBufferLayout vb_tex_layout;
		vb_tex_layout.push_float(2);
		va->addBuffer(*vb_tex, vb_tex_layout, 2);
	}
}