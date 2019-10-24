
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "GroundShader.h"


GroundShader::GroundShader()
{
	viewLoc = 0;
}

GroundShader::~GroundShader()
{
	//dtor
}

void GroundShader::init()
{
	Shader::load("res/glsl/ground.vsh", "res/glsl/ground.fsh");

	Shader::use();
	Shader::setInt(Shader::getLocation("ourTexture"), 0);
	
	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getProjectionMat());

	viewLoc = Shader::getLocation("view");
}

void GroundShader::loadViewMat()
{
	Shader::setMat4(viewLoc, g_pGraphic->getViewMat());
}
