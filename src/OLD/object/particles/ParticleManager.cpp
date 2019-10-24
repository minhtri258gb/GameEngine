
#include <glad/glad.h> // FIXME

#define IMPORT_ENGINE

#include "../../../Main.h"
#include "ParticleManager.h"


ParticleManager::ParticleManager()
{
	shader = new ParticleShader();
}

ParticleManager::~ParticleManager()
{
	delete shader;

	glDeleteBuffers(1, &vboID1);
	glDeleteBuffers(1, &vboID2);
	glDeleteVertexArrays(1, &vaoID);
}

void ParticleManager::init()
{
	// Shader
	shader->init();

	// VAO
	vector<vec2> vertices;
	vertices.push_back(vec2(-0.5f, -0.5f));
	vertices.push_back(vec2(0.5f, -0.5f));
	vertices.push_back(vec2(-0.5f, 0.5f));
	vertices.push_back(vec2(0.5f, 0.5f));

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);

	glGenBuffers(1, &vboID1);
	glBindBuffer(GL_ARRAY_BUFFER, vboID1);
	glBufferData(GL_ARRAY_BUFFER, 32, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, (void*) 0);
	glVertexAttribDivisor(0, 0);

	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, INSTANCE_DATA_LENGTH * MAX_INSTANCE * 4, NULL, GL_STREAM_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, false, INSTANCE_DATA_LENGTH * 4, (void*) (0 * 4));
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, INSTANCE_DATA_LENGTH * 4, (void*) (4 * 4));
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, INSTANCE_DATA_LENGTH * 4, (void*) (8 * 4));
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(4, 4, GL_FLOAT, false, INSTANCE_DATA_LENGTH * 4, (void*) (12 * 4));
	glVertexAttribDivisor(4, 1);
	glVertexAttribPointer(5, 4, GL_FLOAT, false, INSTANCE_DATA_LENGTH * 4, (void*) (16 * 4));
	glVertexAttribDivisor(5, 1);
	glVertexAttribPointer(6, 1, GL_FLOAT, false, INSTANCE_DATA_LENGTH * 4, (void*) (20 * 4));
	glVertexAttribDivisor(6, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindVertexArray(0);

}
