
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "ParticleShader.h"


ParticleShader::ParticleShader()
{
	numOfRowLoc = 0;
}

ParticleShader::~ParticleShader()
{
}

void ParticleShader::init()
{
	Shader::load("res/shader/particleVertex.glsl", "res/shader/particleFragment.glsl");

	Shader::use();
	Shader::setInt(Shader::getLocation("ourTexture"), 0);
	
	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getProjectionMat());

	numOfRowLoc = Shader::getLocation("numOfRow");
}

void ParticleShader::loadNumOfRow(int numOfRow)
{
	Shader::setFloat(numOfRowLoc, numOfRow);
}
