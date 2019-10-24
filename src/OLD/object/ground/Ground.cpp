
#include "../../../Main.h"
#include "Ground.h"


Ground::Ground() {
	shader = new GroundShader();
}

Ground::~Ground() {
	delete shader;
}

void Ground::init() {

	shader->init();

	vector<vec3> vertices;
	vertices.push_back(vec3(   0.0f, -3.0f,    0.0f));
	vertices.push_back(vec3(   0.0f, -3.0f, 1024.0f));
	vertices.push_back(vec3(1024.0f, -3.0f,    0.0f));
	vertices.push_back(vec3(1024.0f, -3.0f, 1024.0f));

	vector<vec2> uvs;
	uvs.push_back(vec2(0.0f, 0.0f));
	uvs.push_back(vec2(0.0f, 1.0f));
	uvs.push_back(vec2(1.0f, 0.0f));
	uvs.push_back(vec2(1.0f, 1.0f));

	vector<vec3> normals;
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));

	vector<unsigned int> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(1); indices.push_back(3); indices.push_back(2);

	m_vb.init();
    m_vb.bind();
    m_vb.setIndex(indices);
    m_vb.addAttribute(vertices);
    m_vb.addAttribute(uvs);
    m_vb.addAttribute(normals);
    m_vb.unbind();

    m_texture.load("res/textures/wall.jpg");

}

void Ground::render() {
	shader->use();
	shader->loadViewMat();

	m_texture.bind();
	m_vb.bind();
	m_vb.draw();
	m_vb.unbind();
}
