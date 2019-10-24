#ifndef __ANIMMODEL_H__
#define __ANIMMODEL_H__

#include "ModelManager.h"

#include "../../API/OpenGL/vao/VertexBufferMain.h"
#include "../../API/OpenGL/texture/Texture2D.h"

#include "../../file/MTMDFile.h"


class AnimModel
{
public:

	// Variable
	static ModelManager *u_manager;

	// Constructor
	AnimModel(MTMDFile*);
	~AnimModel();

	// Framework
	void update();
	void render(vec3 origin, quat angle, float scale);

	// Get / Set
	void setInfo(bool cullface, bool blend);
//	bool isCull();

private:

	// Variable
	VertexBufferMain m_vb;
	vector<unsigned int> m_indices;
	vector<unsigned int> m_rangeVertex;
	vector<Texture2D> m_textures;
//	Texture2D *m_speculateMap;
//	Texture2D *m_normalMap;
//	Texture2D *m_parallaxMap;
	bool m_cullface;
	bool m_blend;
//	short m_atlas;
	int m_actionAnim;
	double m_curtime, m_durationTime;
};

#endif
