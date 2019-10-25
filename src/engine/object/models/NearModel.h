#ifndef __NEARMODEL_H__
#define __NEARMODEL_H__

#include "ModelManager.h"

#include "../../../engine/API/OpenGL/vao/VertexBufferMain.h"
#include "../../../engine/API/OpenGL/texture/Texture2D.h"

#include "../../file/MTMDFile.h"


class NearModel
{
public:

	// Constructor / Destructor
	NearModel(MTMDFile*);
	~NearModel();

	// Framework
	void update();
	void render();

private:

	// Variable
	VertexBufferMain m_vb;
	vector<unsigned int> m_indices;
	vector<unsigned int> m_rangeVertex;
	vector<Texture2D> m_textures;

	// Change data
//	void load(String modelname);
};

#endif
