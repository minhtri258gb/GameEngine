
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../../kernel/Loader.h"
extern Loader *g_pLoader;

#include "../../file/CFGFile.h"

#include "SkyBox.h"


SkyBox::SkyBox()
{
	m_idProgram = m_viewLoc = 0;

	sun = NULL;
}

SkyBox::~SkyBox()
{
	if(sun)
		delete sun;

	g_pGraphic->deleteShader(m_idProgram);
}

void SkyBox::init(string name)
{
	// Data
	CFGFile fCFG("res/skybox/" + name + "/info.cfg");

	// Mesh sky
	vector<vec3> vertices;
	vertices.push_back(vec3( 2.0f,  2.0f,  2.0f));
	vertices.push_back(vec3( 2.0f,  2.0f, -2.0f));
	vertices.push_back(vec3( 2.0f, -2.0f,  2.0f));
	vertices.push_back(vec3( 2.0f, -2.0f, -2.0f));
	vertices.push_back(vec3(-2.0f,  2.0f,  2.0f));
	vertices.push_back(vec3(-2.0f,  2.0f, -2.0f));
	vertices.push_back(vec3(-2.0f, -2.0f,  2.0f));
	vertices.push_back(vec3(-2.0f, -2.0f, -2.0f));

	vector<unsigned int> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(3);
	indices.push_back(0); indices.push_back(3); indices.push_back(2);
	indices.push_back(6); indices.push_back(7); indices.push_back(5);
	indices.push_back(6); indices.push_back(5); indices.push_back(4);
	indices.push_back(2); indices.push_back(3); indices.push_back(7);
	indices.push_back(2); indices.push_back(7); indices.push_back(6);
	indices.push_back(4); indices.push_back(5); indices.push_back(1);
	indices.push_back(4); indices.push_back(1); indices.push_back(0);
	indices.push_back(6); indices.push_back(4); indices.push_back(0);
	indices.push_back(6); indices.push_back(0); indices.push_back(2);
	indices.push_back(5); indices.push_back(7); indices.push_back(3);
	indices.push_back(5); indices.push_back(3); indices.push_back(1);

	m_vb.init();
	m_vb.bind();
	m_vb.addAttribute(vertices);
	m_vb.setIndex(indices);
	m_vb.unbind();

	// Texture sky
	vector<string> textures;
	textures.resize(6);

	string dirfile = "res/skybox/" + name + "/X.tga";
	string listname = "RLUDFB";

	int pos = dirfile.length() - 5;
	for(int i = 0; i < 6; i++)
	{
		textures[i] = dirfile;
		textures[i][pos] = listname[i];
	}

	m_texture.load(textures);

	// Sun
	fCFG.select("[sun]");
	vec3 sunOrigin = fCFG.getVec3("origin");
	if(sunOrigin.length() != 0.0)
		sun = new Sun(sunOrigin);

	// Fog
	fCFG.select("[fog]");
	fogColour = fCFG.getVec3("colour");
	fogColour *= (1.0f / 255.0f);

	// Shader
	m_idProgram = g_pGraphic->loadShader("res/shader/skybox_vertex.glsl", "res/shader/skybox_fragment.glsl");
	g_pGraphic->use(m_idProgram);

	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgram, "ourTexture"), 0);
	g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgram, "projection"), g_pGraphic->getProjectionMat());
	// g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgram, "fogColour"), getFogColour());

	m_viewLoc = g_pGraphic->getLocation(m_idProgram, "view");
}

void SkyBox::render()
{
	g_pGraphic->use(m_idProgram);

	mat4 viewMat = g_pGraphic->getViewMat();
	viewMat[3][0] = viewMat[3][1] = viewMat[3][2] = 0.0f;
	g_pGraphic->setUniform(m_viewLoc, viewMat);
	g_pGraphic->setDepth(false);

	m_texture.bind();

	m_vb.bind();
	m_vb.draw();
	m_vb.unbind();

	g_pGraphic->setDepth(true);
}

vec3 SkyBox::getSunDirect()
{
	if(sun)
		return sun->light->getDirect();
	else
		return vec3();
}

vec3 SkyBox::getSunOrigin()
{
	if(sun)
		return sun->getOrigin();
	else
		return vec3();
}

vec3 SkyBox::getFogColour()
{
	return fogColour;
}
