#ifndef __SHADER_H__
#define __SHADER_H__


class Shader
{
public:

	// Constructor
	Shader();
	virtual ~Shader();

	// General
	virtual void load(string vertexPath, string fragmentPath);
	void use();

	// Get / Set
	unsigned int getLocation(string);

	void setInt(unsigned int location, int);
	void setFloat(unsigned int location, float);
	void setVec2(unsigned int location, vec2);
	void setVec3(unsigned int location, vec3);
	void setVec4(unsigned int location, vec4);
	void setMat4(unsigned int location, mat4);

private:

	// Variable
	unsigned int ID;

	// General
	void checkCompileErrors(unsigned int shader, string type);
};

#endif
