
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "SpriteShader.h"


SpriteShader::SpriteShader()
{
	matViewModelLoc = offsetTexLoc = blendFactorLoc = numOfRowLoc = 0;
}

SpriteShader::~SpriteShader()
{
}

void SpriteShader::init()
{
	Shader::load("res/shader/spriteVertex.glsl", "res/shader/spriteFragment.glsl");

	Shader::use();
	Shader::setInt(Shader::getLocation("ourTexture"), 0);

	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getProjectionMat());

	matViewModelLoc = Shader::getLocation("matViewModel");
	offsetTexLoc = Shader::getLocation("offsetTex");
	blendFactorLoc = Shader::getLocation("blendFactor");
	numOfRowLoc = Shader::getLocation("numOfRow");
}

void SpriteShader::loadMatViewModel(mat4 value)
{
	Shader::setMat4(matViewModelLoc, value);
}

void SpriteShader::loadOffsetTex(vec4 offset)
{
	Shader::setVec4(offsetTexLoc, offset);
}

void SpriteShader::loadBlendFactor(float factor)
{
	Shader::setFloat(blendFactorLoc, factor);
}

void SpriteShader::loadNumOfRow(int numOfRow)
{
	Shader::setFloat(numOfRowLoc, numOfRow);
}
