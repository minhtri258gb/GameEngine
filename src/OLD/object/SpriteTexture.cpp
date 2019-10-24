
#include <fstream>

#include "../../Main.h"
#include "SpriteTexture.h"


SpriteTexture::SpriteTexture() {
	//ctor
}

SpriteTexture::~SpriteTexture() {
	//dtor
}

int SpriteTexture::precache(string name) {
	Texture* texture = new Texture();
	texture->load("res/sprites/"+name+"/texture.tga");

	ifstream file;
	file.open(string("res/sprites/"+name+"/info.cfg").c_str());
	int numOfRow;
	file >> numOfRow;
	file.close();

	listTexture.push_back(texture);
	listNumRow.push_back(numOfRow);

	return listTexture.size() - 1;
}

void SpriteTexture::bind(int idTex) {
	listTexture[idTex]->bindTex();
}

int SpriteTexture::getNumRow(int idTex) {
	return (int)listNumRow[idTex];
}
