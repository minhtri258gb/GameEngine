
#include <glad/glad.h>
#include <stb_image.h>

#include "../../../../Main.h"
#include "Texture2DPack.h"

Texture2DPack::Texture2DPack()
{
}

Texture2DPack::~Texture2DPack()
{
	for(unsigned int index : m_indexs)
		glDeleteTextures(1, &index);
}

void Texture2DPack::bind()
{
	for(unsigned int i=0; i<m_indexs.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, m_indexs[i]);
	}
}

void Texture2DPack::loadAdd(string filename)
{
	unsigned int index;
	glGenTextures(1, &index);
    glBindTexture(GL_TEXTURE_2D, index);

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

    m_indexs.push_back(index);
}
