
#include "../../../Main.h"
#include "SpriteManager.h"


SpriteManager::SpriteManager()
{
	shader = new SpriteShader();
	vao = new VAOStaticDraw();
}

SpriteManager::~SpriteManager()
{
	delete shader;
	delete vao;
}

void SpriteManager::init() {

	// Shader
	shader->init();

	// VAO
	vector<vec2> vertices;
	vertices.push_back(vec2(-0.5f, -0.5f));
	vertices.push_back(vec2( 0.5f, -0.5f));
	vertices.push_back(vec2(-0.5f,  0.5f));
	vertices.push_back(vec2( 0.5f,  0.5f));

	vao->init(1);
	vao->bindVAO();
	vao->createAttribute(0, vertices);
	vao->unbind();
}
