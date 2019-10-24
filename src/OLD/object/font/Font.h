#ifndef __FONT_H__
#define __FONT_H__

#include "FontShader.h"

#define MAX_CHANNEL_TEXT 8


typedef struct {
    string text;
    vec2 position;
    float scale;
    vec3 color;
} t_textdata;

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    ivec2 Size;       // Size of glyph
    ivec2 Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


class Font {
public:

	// Construct
	Font();
	~Font();

	// General
	void init();
	void render();

	// Change data
	void changeText(short idtext, string text, vec2 pos, float scale, vec3 color);
	void setText(short idtext, string text);
	void setText(short idtext, const char *format, ...);

private:

	// Variable
	FontShader* shader;
	unsigned int vaoID, vboID;
	array<t_textdata, MAX_CHANNEL_TEXT> listText;
	map<char, Character> Characters;

	// General
	void renderText(t_textdata);
};

#endif
