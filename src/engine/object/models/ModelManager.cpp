
#include "../../../Main.h"

#include "../../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../kernel/Space.h"
extern Space *g_pSpace;

#include "ModelManager.h"


ModelManager::ModelManager()
{
	m_idProgramS = m_viewLocS = m_modelLocS = 0;
	m_idProgramA = m_viewLocA = m_modelLocA = 0;
}

void ModelManager::init()
{
	// SHADER STATIC
	m_idProgramS = g_pGraphic->loadShader("res/shader/model_static_vertex.glsl", "res/shader/model_static_fragment.glsl");
	g_pGraphic->use(m_idProgramS);

	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramS, "ourTexture"), 0);
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramS, "projection"), g_pGraphic->getProjectionMat());
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramS, "sundir"), g_pSpace->skybox.getSunDirect());
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramS, "fogColour"), g_pSpace->skybox.getFogColour());

	m_modelLocS = g_pGraphic->getLocation(m_idProgramS, "model");
	m_viewLocS = g_pGraphic->getLocation(m_idProgramS, "view");
	
	// SHADER ANIMATION
	m_idProgramA = g_pGraphic->loadShader("res/shader/model_anim_vertex.glsl", "res/shader/model_anim_fragment.glsl");
	g_pGraphic->use(m_idProgramA);

	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramA, "ourTexture"), 0);
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramA, "projection"), g_pGraphic->getProjectionMat());
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramA, "sundir"), g_pSpace->skybox.getSunDirect());
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgramA, "fogColour"), g_pSpace->skybox.getFogColour());

	m_modelLocA = g_pGraphic->getLocation(m_idProgramA, "model");
	m_viewLocA = g_pGraphic->getLocation(m_idProgramA, "view");
}

ModelManager::~ModelManager()
{
	g_pGraphic->deleteShader(m_idProgramS);
	g_pGraphic->deleteShader(m_idProgramA);

	for(StaticModel* model : m_listModelS)
		delete model;
	
	for(AnimModel* model : m_listModelA)
		delete model;
}

void ModelManager::add(StaticModel* model)
{
	m_listModelS.push_back(model);
}

void ModelManager::add(AnimModel* model)
{
	m_listModelA.push_back(model);
}
