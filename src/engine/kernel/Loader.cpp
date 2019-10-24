/*
 * Purpose:
 *  - Quan ly tai toan bo tai nguyen tro choi
 *  - Don dep bo nho truoc khi buoc vao framework
 */

#include <stdio.h>

#define IMPORT_ENGINE
#include "../../Main.h"

#include "../API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "../kernel/System.h"
extern System *g_pSystem;

#include "../kernel/Timer.h"
extern Timer *g_pTimer;

#include "../kernel/View.h"
extern View *g_pView;

#include "../kernel/Command.h"
extern Command *g_pCommand;

#include "../kernel/Space.h"
extern Space *g_pSpace;

#include "../file/CFGFile.h"
#include "../file/LSTFile.h"
#include "../file/MTMDFile.h"

#include "../object/models/StaticModel.h"
#include "../object/models/AnimModel.h"

#include "../../game/object/space/InteractiveEntity.h"
#include "../../game/object/space/ArchitectureEntity.h"
#include "../../game/object/entity/CommonEntity.h"
#include "../../game/object/entity/EquipmentEntity.h"
#include "../../game/object/entity/StaticEntity.h"
#include "Loader.h"


Loader::Loader()
{
}

Loader::~Loader()
{
}

void Loader::setting()
{
	CFGFile *fCFG = new CFGFile("res/system/setting.cfg");

	fCFG->select("[window]");
	g_pGraphic->setWindowWidth(fCFG->getInt("width"));
	g_pGraphic->setWindowHeight(fCFG->getInt("height"));

	fCFG->select("[view]");
	g_pView->setFOV(fCFG->getInt("FOV"));
	g_pView->setNear(fCFG->getInt("near"));
	g_pView->setFar(fCFG->getInt("far"));

	fCFG->select("[time]");
	g_pTimer->setFPSLimit(fCFG->getInt("FPS"));

	fCFG->select("[map]");
	g_pSpace->setMapName(fCFG->get("lastmap"));

	delete fCFG;
}

void Loader::keybind()
{
	ifstream file("res/system/keybind.cfg");
	if(!file.is_open())
	{
		g_pSystem->error("[Loader:keybind] error : file \"res/system/keybind.cfg\" not found!");
		return;
	}

	string line;
	while(getline(file, line))
	{
		if(!line.length() || line[0] == ';')
			continue;
		
		int pos = line.find_first_of(" ");
		g_pCommand->keyBind(line.substr(0, pos), line.substr(pos+1));
	}
}

void Loader::map()
{
	CFGFile fCFG("res/maps/" + g_pSpace->getMapName() + "/info.cfg");

	fCFG.select("[skybox]");
	g_pSpace->skybox.init(fCFG.get("name"));

	fCFG.select("[terrain]");
	g_pSpace->terrain.init(fCFG.get("name"));

	fCFG.select("[construct]");

	fCFG.select("[player]");
	vec3 origin;
	string data = fCFG.get("origin");
	sscanf(data.c_str(), "%f %f %f", &origin.x, &origin.y, &origin.z);
	engine.m_mainPlayer->setOrigin(origin);
}

void Loader::entity()
{
	typedef struct
	{
		bool anim;
		int modelId;
		vec3 origin;
		int angle;
		float scale;
	} t_rawent;

	// Variable
	vector<t_rawent> listEnt;
	vector<string> listMdlName;

	LSTFile fLST("res/maps/" + g_pSpace->getMapName() + "/entities.txt");
	while(fLST.next())
	{
		// Entity data
		t_rawent ent;

		string modelname = fLST.getString();
		ent.modelId = -1;
		ent.origin = fLST.getVec3();
		ent.angle = fLST.getInt();
		ent.scale = fLST.getFloat();

		for(unsigned int i=0; i< listMdlName.size(); i++)
			if(listMdlName.at(i) == modelname)
				ent.modelId = i;
		
		if(ent.modelId == -1)
		{
			ent.modelId = listMdlName.size();
			listMdlName.push_back(modelname);
		}

		listEnt.push_back(ent);
	}

	// Model loader
	vector<MTMDFile*> listMdlFile;
	vector<bool> l_animMdl;
	for(unsigned int i = 0; i < listMdlName.size(); i++)
	{
		string modelname = listMdlName.at(i);
		string filedir = "res/models/"+modelname+"/";
		CFGFile fCFG(filedir+"info.cfg");

		fCFG.select("[general]");
		string filepath = filedir+fCFG.get("model");

		MTMDFile *fMTMD = new MTMDFile();
		if(!fMTMD->load(filepath))
		{
			g_pSystem->error("[Loader::entity] Can't load model " + modelname);
			continue;
		}
		listMdlFile.push_back(fMTMD);
		l_animMdl.push_back(fMTMD->m_frame_position.size() ? true : false);
	}

	// Create Model
	vector<StaticModel*> listModelS;
	vector<AnimModel*> listModelA;
	int indexS = 0, indexA = 0;
	vector<int> l_pointerMdl;
	for(MTMDFile *file : listMdlFile)
	{
		if(file->m_frame_position.size())
		{
			l_pointerMdl.push_back(indexA);
			indexA++;
			listModelA.push_back(new AnimModel(file));
		}
		else
		{
			l_pointerMdl.push_back(indexS);
			indexS++;
			listModelS.push_back(new StaticModel(file));
		}
	}
	
	// Create Entity
	for(t_rawent ent : listEnt)
		if(l_animMdl.at(ent.modelId))
			g_pSpace->add(new EquipmentEntity(listModelA.at(l_pointerMdl.at(ent.modelId)), ent.origin, ent.angle, ent.scale));
		else
			g_pSpace->add(new CommonEntity(listModelS.at(l_pointerMdl.at(ent.modelId)), ent.origin, ent.angle, ent.scale));
}

void Loader::stora()
{
	// LSTFile fLST("res/maps/" + engine.map->getName() + "/stora.txt");
	// while(fLST.next())
	// {
	// 	string type = fLST.getString();

	// 	if(type == "weapon")
	// 	{
	// 		IQMFile *file = new IQMFile();
	// 		file->load("res/models/" + fLST.getString() + "/model.iqm");
	// 		engine.precache->stora(type, file);
	// 	}
	// 	else
	// 		Log::console("[Loader : stora] type not match: " + type);
	// }
}

//void Loader::entity()
//{
//	LSTFile fLST("res/maps/" + engine.map->getName() + "/entities.txt");
//	while(fLST.next())
//	{
//		// Entity data
//		string type = fLST.getString();
//		string modelname = fLST.getString();
//		vec3 origin = fLST.getVec3();
//		quat angle(fLST.getInt());
//		float scale = fLST.getFloat();
//
//		string filedir = "res/models/"+modelname+"/";
//
//		// Model data
//		CFGFile fCFG(filedir+"info.cfg");
//		fCFG.select("[general]");
//
//		ModelFile fMdl;
//		if(!fMdl.load(filedir+fCFG.get("model")))
//		{
//			Log::console("[Loader : entity] Can't load model "+modelname);
//			continue;
//		}
//
//		if(type == "static")
//		{
//			if(fMdl.getNumMesh() != 1)
//			{
//				Log::console("[Loader : entity] this model not support static model "+modelname);
//				continue;
//			}
//
//			// Mesh
//			StaticModel *model = new StaticModel();
//			model->buildMesh(fMdl.getVertices(0), fMdl.getUVs(0), fMdl.getNormals(0), fMdl.getIndices(0));
//
//			fCFG.select("[mesh]");
//			bool cullface = fCFG.getBool("cullface");
//			bool blend = fCFG.getBool("blend");
//
//			model->setInfo(cullface, blend);
//
//			// Texture
//			if(fMdl.getNumTexture())
//				model->buildTexture(fMdl.getNameTexture(0));
//			else
//			{
//				fCFG.select("[texture]");
//				string filetexture = filedir + fCFG.get("main");
//				if(File::fileexist(filetexture))
//					model->buildTexture(filetexture);
//				else
//					model->buildTexture("res/models/default/texture.tga");
//			}
//
//			engine.space.modelManager.add(model);
//
//			// Body
//			fCFG.select("[body]");
//			vec3 boundingbox;
//			string data = fCFG.get("size");
//			sscanf(data.c_str(), "%f %f %f", &boundingbox.x, &boundingbox.y, &boundingbox.z);
//			boundingbox *= scale;
//			BodyBox *body = new BodyBox(boundingbox, origin, angle, true);
//
//			// Entity
//			StaticEntity *entity = new StaticEntity(model, body, origin, angle, scale);
//
//			engine.space.add(entity);
//		}
//
////		else if(type == "common")
////		{
////
////			engine.space.add(
////					new CommonEntity(fLST.getString(), fLST.getString(), fLST.getVec3(), fLST.getInt(), fLST.getFloat()));
////		}
////		else if(type == "architecture")
////			engine.space.add(
////					new ArchitectureEntity(fLST.getString(), fLST.getString(), fLST.getVec3(), fLST.getInt(), fLST.getFloat()));
////		else if(type == "interactive")
////			engine.space.add(
////					new InteractiveEntity(fLST.getString(), fLST.getString(), fLST.getVec3(), fLST.getInt(), fLST.getFloat()));
////		else if(type == "equipment")
////		{
////			EquipmentEntity *equipmentEnt = new EquipmentEntity(
////					fLST.getString());
////			engine.equipmentManager->add(equipmentEnt);
//////			engine.actionItem->set(equipmentEnt);
////		}
////		else
////			Log::console("[Loader : loadEntities] type not match: " + type);
//	}
//}
