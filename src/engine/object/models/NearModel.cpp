
#include <glm/gtc/matrix_transform.hpp>

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/View.h"
extern View *g_pView;

#include "../../../engine/kernel/Manager.h"
extern Manager *g_pManager;

#include "../../../engine/file/CFGFile.h"
#include "AnimModel.h"
#include "NearModel.h"


NearModel::NearModel(MTMDFile *file)
{
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

	// AnimModel::u_manager->add(this);
}

NearModel::~NearModel()
{
}

void NearModel::update()
{
}

void NearModel::render()
{
}
