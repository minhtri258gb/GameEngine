#ifndef NEARMODEL_H_
#define NEARMODEL_H_

#include "../../../engine/API/OpenGL/vao/VertexBufferMultiID.h"
#include "../../../engine/API/OpenGL/texture/Texture2D.h"


class NearModel
{
public:

	// Constructor
	NearModel(VertexBufferMultiID*, vector<Texture2D*>);
	~NearModel();

	// General
	void update();
	void render();

private:

	// Variable
	VertexBufferMultiID* m_vb;
	vector<Texture2D*> m_textures;

	// Change data
//	void load(String modelname);
};

#endif
