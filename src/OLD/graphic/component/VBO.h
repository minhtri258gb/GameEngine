#ifndef VBO_H
#define VBO_H


class VBO {
public:

	// Constructor
	VBO();
	~VBO();

	// General
	void bindVBO();
	void unbind();

protected:

private:
	unsigned int ID;
};

#endif
