
#include <map>
#include <glad/glad.h> // FIXME

#include <ft2build.h>
#include FT_FREETYPE_H

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../../engine/kernel/System.h"
extern System *g_pSystem;

#include "Font.h"


Font::Font()
{
	shader = new FontShader();
	vaoID = vboID = 0;
}

Font::~Font()
{
	delete shader;
}

void Font::init()
{

	// Init Font
	FT_Library ft;
	if(FT_Init_FreeType(&ft))
	{
		std::cout << "[error] Font: Could not init freetype library"
				<< std::endl;
		g_pSystem->exit();
	}

	FT_Face face;
	if(FT_New_Face(ft, "res/font/FreeSans.ttf", 0, &face))
	{
		std::cout << "[error] Font: Could not open font" << std::endl;
		g_pSystem->exit();
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for(GLubyte c = 32; c < 128; c++)
	{

		// Load character glyph
		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "[warn] Font: Failed to load Glyph" << std::endl;
			continue;
		}

		FT_GlyphSlot g = face->glyph;

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RED, g->bitmap.width, g->bitmap.rows, 0,
		GL_RED,
		GL_UNSIGNED_BYTE, g->bitmap.buffer);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {texture, ivec2(g->bitmap.width,
				g->bitmap.rows), ivec2(g->bitmap_left, g->bitmap_top),
				(unsigned int) g->advance.x};
		Characters.insert(std::pair<GLchar,Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Shader
	shader->init();

	// VAO
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
			GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Font::render()
{
	shader->use();

	g_pGraphic->setBlend(true, 1);
	g_pGraphic->setDepth(false);

	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(0);

	glActiveTexture(GL_TEXTURE0);

	for(t_textdata text : listText)
		renderText(text);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

	g_pGraphic->setBlend();
	g_pGraphic->setDepth();
}

void Font::changeText(short idtext, string text, vec2 pos, float scale, vec3 color)
{
	t_textdata newtext;
	newtext.text = text;
	newtext.position = pos;
	newtext.scale = scale;
	newtext.color = color;
	listText[idtext] = newtext;
}

void Font::setText(short idtext, string text)
{
	listText[idtext].text = text;
}

void Font::setText(short idtext, const char *format, ...)
{
	va_list argList;
	va_start(argList, format);
	int lengthString = _vscprintf(format, argList) + 1;
	char *cstr = new char[lengthString];
	vsprintf(cstr, format, argList);
	listText[idtext].text = cstr;
	delete[] cstr;
}

void Font::renderText(t_textdata text)
{
	shader->loadColor(text.color.x, text.color.y, text.color.z);

	text.position.x *= g_pGraphic->getWindowWidth();
	text.position.y *= g_pGraphic->getWindowHeight();
	vec2 offset = text.position;

	for(auto c : text.text)
	{

		Character ch = Characters[c];

		// new line
		if(c == 10)
		{
			offset.x = text.position.x;
			offset.y -= 50.0f * text.scale;
			continue;
		}

		float xpos = offset.x + ch.Bearing.x * text.scale;
		float ypos = offset.y - (ch.Size.y - ch.Bearing.y) * text.scale;

		float w = ch.Size.x * text.scale;
		float h = ch.Size.y * text.scale;

		// Update VBO for each character
		float vertices[6][4] = {{xpos, ypos + h, 0.0, 0.0}, {xpos, ypos, 0.0,
				1.0}, {xpos + w, ypos, 1.0, 1.0},

		{xpos, ypos + h, 0.0, 0.0}, {xpos + w, ypos, 1.0, 1.0}, {xpos + w, ypos
				+ h, 1.0, 0.0}};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		offset.x += (ch.Advance >> 6) * text.scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
}
