
#include <array>

#include <glm/glm.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "ModelShader.h"

ModelShader::ModelShader()
{
	modelLoc = viewLoc = 0;
}

ModelShader::~ModelShader()
{
	//dtor
}

void ModelShader::init()
{
	Shader::load("res/shader/modelVertex.glsl", "res/shader/modelFragment.glsl");

	Shader::use();
	Shader::setInt(Shader::getLocation("ourTexture"), 0);
	
	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getProjectionMat());
//	Shader::setVec3(Shader::getLocation("sundir"), engine.skybox->getSunDirect());
//	Shader::setVec3(Shader::getLocation("fogColour"), engine.skybox->getFogColour());

	modelLoc = Shader::getLocation("model");
	viewLoc = Shader::getLocation("view");
}

void ModelShader::loadViewMat()
{
	Shader::setMat4(viewLoc, g_pGraphic->getViewMat());
}

void ModelShader::loadModelMat(mat4 value)
{
	Shader::setMat4(modelLoc, value);
}
