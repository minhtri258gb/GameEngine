
#include "../../../Main.h"
#include "Model.h"


Model::Model()
{
	cullface = true;
	atlas = 1;
}

Model::~Model()
{
}

void Model::render(vec3 origin, quat angle, float scale)
{

}

void Model::setCullface(bool value)
{
	cullface = value;
}

void Model::setTextureAtlas(short value)
{
	atlas = value;
}
