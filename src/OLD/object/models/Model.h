#ifndef __MODEL_H__
#define __MODEL_H__

class Model
{
public:

	// Constructor
	Model();
	virtual ~Model();

	// Framework
	virtual void render(vec3 origin, quat angle, float scale);

	// Get / Set
	void setCullface(bool);
	void setTextureAtlas(short);

protected:

	// Variable
	bool cullface;
	short atlas = 1;
};

#endif
