
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "FontShader.h"


FontShader::FontShader()
{
	colorLoc = 0;
}

FontShader::~FontShader()
{
}

void FontShader::init()
{
	Shader::load("res/shader/fontVertex.glsl", "res/shader/fontFragment.glsl");

	Shader::use();
	Shader::setInt(Shader::getLocation("ourTexture"), 0);
	
	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getOrthoMat());

	colorLoc = Shader::getLocation("color");
}

void FontShader::loadColor(float r, float g, float b)
{
	Shader::setVec3(colorLoc, vec3(r, g, b));
}
