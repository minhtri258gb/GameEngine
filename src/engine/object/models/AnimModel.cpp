
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../kernel/System.h"
extern System *g_pSystem;

#include "../../kernel/Timer.h"
extern Timer *g_pTimer;

#include "../../kernel/Manager.h"
extern Manager *g_pManager;

#include "../../kernel/View.h"
extern View *g_pView;

#include "AnimModel.h"


ModelManager* AnimModel::u_manager = NULL;


AnimModel::AnimModel(MTMDFile *file)
{
	m_cullface = true;
	m_blend = false;
	m_actionAnim = 0;
	m_curtime = 0.0;
	m_durationTime = 0.0;

	m_vb.init();
	m_vb.bind();
	m_vb.addAttribute(file->m_vertices);
	m_vb.addAttribute(file->m_normals);
	m_vb.addAttribute(file->m_uvs);
	m_vb.addAttribute(file->m_idbone);
	m_vb.addAttribute(file->m_weight);
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

AnimModel::~AnimModel()
{
}

void AnimModel::update()
{
	// if ( m_iNumFrames < 1 ) return;
 
    // m_fAnimTime += fDeltaTime;
 
    // while ( m_fAnimTime > m_fAnimDuration ) m_fAnimTime -= m_fAnimDuration;
    // while ( m_fAnimTime < 0.0f ) m_fAnimTime += m_fAnimDuration;
 
    // // Figure out which frame we're on
    // float fFramNum = m_fAnimTime * (float)m_iFramRate;
    // int iFrame0 = (int)floorf( fFramNum );
    // int iFrame1 = (int)ceilf( fFramNum );
    // iFrame0 = iFrame0 % m_iNumFrames;
    // iFrame1 = iFrame1 % m_iNumFrames;
 
    // float fInterpolate = fmodf( m_fAnimTime, m_fFrameDuration ) / m_fFrameDuration;
 
    // InterpolateSkeletons( m_AnimatedSkeleton, m_Skeletons[iFrame0], m_Skeletons[iFrame1], fInterpolate );
}

void AnimModel::render(vec3 _origin, quat _angle, float _scale)
{
	if(!g_pView->frustumCulling.isSphereInFrustum(_origin, 100)) // SIZEBOX
		return;

	g_pGraphic->use(u_manager->m_idProgramA);
	g_pGraphic->setUniform(u_manager->m_viewLocA, g_pGraphic->getViewMat());

	mat4 tranformMat = translate(mat4(1.0f), _origin);
	tranformMat *= toMat4(_angle);
	tranformMat = scale(tranformMat, vec3(_scale, _scale, _scale));
	g_pGraphic->setUniform(u_manager->m_modelLocA, tranformMat);

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

void AnimModel::setInfo(bool cullface, bool blend)
{
	m_cullface = cullface;
	m_blend = blend;
}
