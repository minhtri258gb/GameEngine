
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "DebugShader.h"


DebugShader::DebugShader()
{
	viewLoc = modelLoc = 0;
}

void DebugShader::init()
{
	Shader::load("res/shader/debugVertex.glsl", "res/shader/debugFragment.glsl");

	Shader::use();

	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getProjectionMat());

	viewLoc = Shader::getLocation("view");
	modelLoc = Shader::getLocation("model");
}

DebugShader::~DebugShader()
{
}

void DebugShader::loadViewMat()
{
	Shader::setMat4(viewLoc, g_pGraphic->getViewMat());
}

void DebugShader::loadModelMat(mat4 value)
{
	Shader::setMat4(modelLoc, value);
}
