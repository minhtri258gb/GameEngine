
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../kernel/Space.h"
extern Space *g_pSpace;

#include "TerrainShader.h"


TerrainShader::TerrainShader()
{
	viewLoc = levelQuadLoc = 0;
}

void TerrainShader::init()
{
	Shader::load("res/shader/terrainVertex.glsl", "res/shader/terrainFragment.glsl");

	Shader::use();
	Shader::setInt(Shader::getLocation("textureMain"), 0);
	Shader::setInt(Shader::getLocation("texDetailR"), 1);
	Shader::setInt(Shader::getLocation("texDetailG"), 2);
	Shader::setInt(Shader::getLocation("texDetailB"), 3);
	Shader::setInt(Shader::getLocation("texDetailA"), 4);
	Shader::setInt(Shader::getLocation("texPartR"), 5);
	Shader::setInt(Shader::getLocation("texPartG"), 6);
	Shader::setInt(Shader::getLocation("texPartB"), 7);
	Shader::setInt(Shader::getLocation("texPartA"), 8);

	Shader::setMat4(Shader::getLocation("projection"), g_pGraphic->getProjectionMat());
	Shader::setVec3(Shader::getLocation("sundir"), g_pSpace->skybox.getSunDirect());
	Shader::setVec3(Shader::getLocation("fogColour"), g_pSpace->skybox.getFogColour());

	viewLoc = Shader::getLocation("view");
	levelQuadLoc = Shader::getLocation("levelQuad");

}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::loadViewMat()
{
	Shader::setMat4(viewLoc, g_pGraphic->getViewMat());
}

void TerrainShader::loadLevelQuad(unsigned char levelquad)
{
	Shader::setFloat(levelQuadLoc, (float) levelquad);
}
