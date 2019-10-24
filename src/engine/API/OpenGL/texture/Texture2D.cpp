
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../../../../Main.h"
#include "Texture2D.h"


Texture2D::Texture2D()
{
	m_index = 0;
}

Texture2D::Texture2D(string filename)
{
	m_index = 0;
	load(filename);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_index);
}

void Texture2D::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_index);
}

void Texture2D::load(string filename)
{
	glGenTextures(1, &m_index);
    glBindTexture(GL_TEXTURE_2D, m_index);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if(data)
    {
		glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else cout << "[Texture] Failed to load texture: "+filename << endl;

    stbi_image_free(data);
}
