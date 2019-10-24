#include <glad/glad.h>
#include <stb_image.h>

#include "../../../../Main.h"
#include "TextureCube.h"


TextureCube::TextureCube()
{
	m_index = 0;
}

TextureCube::~TextureCube()
{
	glDeleteTextures(6, &m_index);
}

void TextureCube::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_index);
}

void TextureCube::load(vector<string> listFilename)
{
	glGenTextures(1, &m_index);

	if(listFilename.size() != 6)
	{
		cout << "[Texture] Need 6 file to load cube texture" << endl;
		return;
	}

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_index);

    int width, height, nrChannels;
	for(int i = 0; i < 6; i++)
	{
		unsigned char *data = stbi_load(listFilename[i].c_str(), &width, &height, &nrChannels, 0);
		if(data)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
	    	cout << "[Texture] Failed to load texture: "+listFilename.at(i) << endl;

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
