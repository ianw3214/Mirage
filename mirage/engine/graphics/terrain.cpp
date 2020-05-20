#include "terrain.hpp"

Terrain::Terrain(int x, int y)
    : m_x(x * kSize)
    , m_y(y * kSize)
    , m_model(nullptr)
{
    GenerateTerrain();
}

void Terrain::GenerateTerrain()
{
    constexpr int count = kVertexCount * kVertexCount;
    float * vertices = new float[count * 3];
    float * normals = new float[count * 3];
    float * textures = new float[count * 2];
    constexpr unsigned int num_indices = 6 * (kVertexCount - 1) * (kVertexCount - 1);
    unsigned int * indices = new unsigned int[num_indices];
    int vertexIndex = 0;
    for (int i = 0; i < kVertexCount; ++i)
    {
        for (int j = 0; j < kVertexCount; ++j)
        {
            vertices[vertexIndex * 3] = -(float)j / ((float) kVertexCount - 1) * kSize + m_x;
            vertices[vertexIndex * 3 + 1] = 0;
            vertices[vertexIndex * 3 + 2] = -(float)i / ((float)kVertexCount - 1) * kSize + m_y;
            normals[vertexIndex * 3] = 0;
            normals[vertexIndex * 3 + 1] = 1;
            normals[vertexIndex * 3 + 2] = 0;
            textures[vertexIndex * 2] = ((float) j / ((float) kVertexCount - 1)) * 20.f / 2.f;
            textures[vertexIndex * 2 + 1] = ((float) i / ((float) kVertexCount - 1)) * 20.f / 2.f;
            vertexIndex++;
        }
    }
    int index = 0;
    for (int y = 0; y < kVertexCount - 1; ++y)
    {
        for (int x = 0; x < kVertexCount - 1; ++x)
        {
            unsigned int topLeft = (y * kVertexCount) + x;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = (y + 1) * kVertexCount + x;
            unsigned int bottomRight = bottomLeft + 1;
            indices[index++] = topLeft;
            indices[index++] = bottomLeft;
            indices[index++] = topRight;
            indices[index++] = topRight;
            indices[index++] = bottomLeft;
            indices[index++] = bottomRight;
        }
    }

    m_model = new RawModel(indices, num_indices);
    {   // VERTEX POSITIONS BUFFER
        m_model->vbs.emplace_back(vertices, sizeof(float) * count * 3);
        VertexBuffer& vb_pos = m_model->vbs[0];
        VertexBufferLayout vb_pos_layout;
        vb_pos_layout.pushFloat(3);
        m_model->va.addBuffer(vb_pos, vb_pos_layout, 0);
    }
    {	// SETUP VERTEX NORMALS BUFFER
		m_model->vbs.emplace_back(normals, sizeof(float) * count * 3);
		VertexBuffer& vb_nrm = m_model->vbs[1];
		VertexBufferLayout vb_nrm_layout;
		vb_nrm_layout.pushFloat(3);
		m_model->va.addBuffer(vb_nrm, vb_nrm_layout, 1);
	}
	{	// SETUP VERTEX TEXTURES BUFFER
		m_model->vbs.emplace_back(textures, sizeof(float) * count * 2);
		VertexBuffer& vb_tex = m_model->vbs[2];
		VertexBufferLayout vb_tex_layout;
		vb_tex_layout.pushFloat(2);
		m_model->va.addBuffer(vb_tex, vb_tex_layout, 2);
	}
    m_model->SetTexture("res/grass.png");
}