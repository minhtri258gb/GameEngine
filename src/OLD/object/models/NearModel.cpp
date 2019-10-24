
#include <glm/gtc/matrix_transform.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/View.h"
extern View *g_pView;

#include "../../../engine/kernel/Manager.h"
extern Manager *g_pManager;

#include "../../../engine/file/CFGFile.h"
#include "NearModel.h"


NearModel::NearModel(VertexBufferMultiID* vb, vector<Texture2D*> listTex)
{
	m_vb = vb;
	m_textures = listTex;
}

NearModel::~NearModel()
{
	delete m_vb;

	for(Texture2D* pTex : m_textures)
		delete pTex;
}

void NearModel::update()
{
}

void NearModel::render()
{
//	Vec3 origin = engine->view->getPosition();
	vec3 origin(8199, 251, 21468);
	quat angle = g_pView->getQuat();
	float _scale = 1.0f;

	ModelShader *shader = &g_pManager->modelshader;

	shader->use();
	shader->loadViewMat();

	mat4 transform = translate(mat4(), origin);
	transform *= toMat4(angle);
	transform = scale(transform, vec3(_scale, _scale, _scale));

	shader->loadModelMat(transform);

//	m_textures[m_texPointer[count]]->bind();
	m_vb->bind();
	for(unsigned int i=0; i<m_vb->getNumPart(); i++)
		m_vb->draw(i);
	m_vb->unbind();
}
