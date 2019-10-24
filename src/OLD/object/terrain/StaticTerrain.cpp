
#include <stb_image.h>

#include "../../../Main.h"
#include "StaticTerrain.h"

#include "../../../engine/file/BTFile.h"

#define MAXHEIGHTTERR 8.0f
#define CELLSPACE 10

StaticTerrain::StaticTerrain()
{
	shader = new TerrainShader();
	vao = new VAOStaticDraw();
	texture = new Texture();
}

StaticTerrain::~StaticTerrain()
{
	delete shader;
	delete vao;
	delete texture;
}

void StaticTerrain::init(CFGFile *fCFG)
{

	// Shader
	shader->init();

	// Data
	fCFG->select("[terrain]");
	string terrainName = fCFG->get("name");

	BTFile *filebt = new BTFile("res/terrain/" + terrainName + "/heightmap.bt");

	float depth = filebt->getRows();
	float width = filebt->getColumns();

	// VAO

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<unsigned int> indices;
	for(int z = 0; z < depth; z++)
	{
		for(int x = 0; x < width; x++)
		{

//			float height = (float)data[z*width + x] * 0.3f;
			float height = filebt->getData(depth - z - 1, x);
			float xc = x * CELLSPACE;
			float zc = z * CELLSPACE;

			vertices.push_back(vec3(xc, height, zc));
			uvs.push_back(vec2(x * 1.0 / width, z * 1.0 / depth));
		}
	}
	for(int z = 0; z < depth - 1; z++)
	{
		for(int x = 0; x < width - 1; x++)
		{
			indices.push_back((z) * width + (x));
			indices.push_back((z + 1) * width + (x));
			indices.push_back((z) * width + (x + 1));
			indices.push_back((z + 1) * width + (x));
			indices.push_back((z + 1) * width + (x + 1));
			indices.push_back((z) * width + (x + 1));
		}
	}

	vao->init(2);
	vao->bindVAO();
	vao->createIndexBuffer(indices);
	vao->createAttribute(0, vertices);
	vao->createAttribute(1, uvs);
	vao->unbind();

	// Texture
	texture->load("res/textures/wall_512_1_05.tga");
}

void StaticTerrain::render()
{
	shader->use();
	shader->loadViewMat();

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	texture->bindTex();

	vao->bindVAO();
	vao->draw();
	vao->unbind();

//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
