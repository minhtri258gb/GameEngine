
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../kernel/System.h"
extern System *g_pSystem;

#include "../../kernel/View.h"
extern View *g_pView;

#include "../../kernel/Manager.h"
extern Manager *g_pManager;

#include "StaticModel.h"


ModelManager* StaticModel::u_manager = NULL;


StaticModel::StaticModel(MTMDFile *file)
{
	m_cullface = true;
	m_blend = false;

	m_vb.init();
	m_vb.bind();
	m_vb.addAttribute(file->m_vertices);
	m_vb.addAttribute(file->m_normals);
	m_vb.addAttribute(file->m_uvs);
	m_vb.unbind();

	for(unsigned int index : file->m_indices)
		m_indices.push_back(index);

	for(int i : file->m_meshs_offset)
		m_rangeVertex.push_back(i * 3);
	m_rangeVertex.push_back(file->m_vertices.size() * 3);

	m_textures.resize(file->m_meshs_materials.size());
	for(unsigned int i = 0; i < m_textures.size(); i++)
		m_textures[i].load(file->m_filedir+file->m_meshs_materials.at(i));

	u_manager->add(this);
}

StaticModel::~StaticModel()
{
}

void StaticModel::render(vec3 _origin, quat _angle, float _scale)
{
	// // if(!g_pView->frustumCulling.isSphereInFrustum(_origin, 100)) // SIZEBOX
	// // 	return;

	g_pGraphic->use(u_manager->m_idProgramS);
	g_pGraphic->setUniform(u_manager->m_viewLocS, g_pGraphic->getViewMat());

	mat4 tranformMat = translate(mat4(1.0f), _origin);
	tranformMat *= toMat4(_angle);
	tranformMat = scale(tranformMat, vec3(_scale, _scale, _scale));
	g_pGraphic->setUniform(u_manager->m_modelLocS, tranformMat);

	g_pGraphic->setCullface(m_cullface);
	// g_pGraphic->setBlend(m_blend, 1);
	// // g_pGraphic->setDepth(false);

	m_vb.bind();
	for(unsigned int i = 0; i < m_textures.size(); i++)
	{
		m_textures[i].bind();

		unsigned int start = m_rangeVertex.at(i);
		m_vb.drawElements(m_rangeVertex.at(i+1) - start, &m_indices[start]);
	}
	m_vb.unbind();

	g_pGraphic->setCullface();
	// g_pGraphic->setBlend();
	// // g_pGraphic->setDepth();
}

void StaticModel::setInfo(bool cullface, bool blend)
{
	m_cullface = cullface;
	m_blend = blend;
}
