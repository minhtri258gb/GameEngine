#ifndef __VBOSTATICDRAW_H__
#define __VBOSTATICDRAW_H__

#include "VBO.h"


class VBOStaticDraw : public VBO {
public:

	// Change data
	void storeData(vector<vec3> data);
	void storeData(vector<vec2> data);

private:
};

#endif
