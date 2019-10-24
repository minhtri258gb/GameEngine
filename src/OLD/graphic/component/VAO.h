#ifndef VAO_H_
#define VAO_H_


class VAO {
public:

	// Constructor
	VAO();
	~VAO();

	// General
	void init(int attributes);
	void bindVAO();
	void unbind();
	void draw(bool ebo);

protected:
	int attributes;
	int indexCount;

private:
	unsigned int ID;
};

#endif
