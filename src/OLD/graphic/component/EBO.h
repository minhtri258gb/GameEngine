#ifndef EBO_H
#define EBO_H

#include <vector>


class EBO {
public:

	// Constructor
	EBO();
	~EBO();

	// General
	void bindEBO();
	void unbind();

protected:

private:
	unsigned int ID;
};

#endif
