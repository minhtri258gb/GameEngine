
#define IMPORT_ENGINE
#include "../../Main.h"

#include "../kernel/System.h"
extern System *g_pSystem;

#include "MTMDFile.h"


MTMDFile::MTMDFile()
{
}

MTMDFile::~MTMDFile()
{
}

bool MTMDFile::load(string filepath)
{
	int pos = filepath.find_last_of("/");
	m_filedir = filepath.substr(0, pos+1);

	ifstream file(filepath.c_str(), ios::in | ios::binary);

	if(!file.is_open())
	{
		g_pSystem->log("[MTMDFile::load] File not found: " + filepath);
		return false;
	}

	// Read header
	char marker[15];
	file.read(marker, 14);
	marker[14] = '\0';
	if(string(marker) != "MasterModelBIN")
	{
		g_pSystem->log("[MTMDFile::load] File format invail: " + filepath);
		return false;
	}

	short version = 0;
	file.read(reinterpret_cast<char*>(&version), 2);
	if(version != 1)
	{
		g_pSystem->log("[MTMDFile::load] File version invail: " + filepath);
		return false;
	}

	int ofs_vertices, ofs_indices, ofs_meshs, ofs_bones, ofs_tranforms, ofs_anims;
	file.read(reinterpret_cast<char*>(&ofs_vertices), 4);
	file.read(reinterpret_cast<char*>(&ofs_indices), 4);
	file.read(reinterpret_cast<char*>(&ofs_meshs), 4);
	file.read(reinterpret_cast<char*>(&ofs_bones), 4);
	file.read(reinterpret_cast<char*>(&ofs_tranforms), 4);
	file.read(reinterpret_cast<char*>(&ofs_anims), 4);

	int numloop = 0;

	cout << "offset" << endl;
	cout << ofs_vertices << endl;
	cout << ofs_indices << endl;
	cout << ofs_meshs << endl;
	cout << ofs_bones << endl;
	cout << ofs_tranforms << endl;
	cout << ofs_anims << endl;

	// Vertices
	file.seekg(ofs_vertices);
	file.read(reinterpret_cast<char*>(&numloop), 4);

	vec3 vertices_origin;
	vec3 vertices_normal;
	vec2 vertices_uv;
	ivec3 vertices_idbone;
	vec3 vertices_weight;

	for(int i = 0; i < numloop; i++)
	{
		file.read(reinterpret_cast<char*>(&vertices_origin), 12);
		file.read(reinterpret_cast<char*>(&vertices_normal), 12);
		file.read(reinterpret_cast<char*>(&vertices_uv), 8);
		file.read(reinterpret_cast<char*>(&vertices_idbone[0]), 12);
		file.read(reinterpret_cast<char*>(&vertices_weight), 12);
		m_vertices.push_back(vertices_origin);
		m_normals.push_back(vertices_normal);
		m_uvs.push_back(vertices_uv);
		m_idbone.push_back(vertices_idbone);
		m_weight.push_back(vertices_weight);
	}

	// Indices
	file.seekg(ofs_indices);
	file.read(reinterpret_cast<char*>(&numloop), 4);

	unsigned int indices_index;

	for(int i = 0; i < numloop; i++)
	{
		file.read(reinterpret_cast<char*>(&indices_index), 4);
		m_indices.push_back(indices_index);
		file.read(reinterpret_cast<char*>(&indices_index), 4);
		m_indices.push_back(indices_index);
		file.read(reinterpret_cast<char*>(&indices_index), 4);
		m_indices.push_back(indices_index);
	}

	for(unsigned int iz = 0; iz<m_indices.size()/3; iz++)
		cout << m_indices[iz*3] << " " << m_indices[iz*3+1] << " " << m_indices[iz*3+2] << endl;

	// Meshs
	file.seekg(ofs_meshs);
	file.read(reinterpret_cast<char*>(&numloop), 4);

	int mesh_offset;
	char texture_name[64];

	for(int i=0; i<numloop; i++)
	{
		file.read(reinterpret_cast<char*>(&mesh_offset), 4);
		file.read(reinterpret_cast<char*>(&texture_name), 64);
		m_meshs_offset.push_back(mesh_offset);
		m_meshs_materials.push_back(texture_name);
	}

	// Bones
	file.seekg(ofs_bones);
	file.read(reinterpret_cast<char*>(&numloop), 4);

	int num_bone = numloop;
	char bone_name[32];
	int bone_parent;

	for(int i=0; i<numloop; i++)
	{
		file.read(reinterpret_cast<char*>(&bone_name), 32);
		file.read(reinterpret_cast<char*>(&bone_parent), 4);
		m_bones_name.push_back(bone_name);
		m_bones_parent.push_back(bone_parent);
	}

	// Tranforms
	file.seekg(ofs_tranforms);
	file.read(reinterpret_cast<char*>(&numloop), 4);
	numloop *= num_bone;

	vec3 tranforms_position;
	vec4 tranforms_rotate;
	vec3 tranforms_scale;
	for(int i=0; i<numloop; i++)
	{
		file.read(reinterpret_cast<char*>(&tranforms_position), 12);
		file.read(reinterpret_cast<char*>(&tranforms_rotate), 16);
		file.read(reinterpret_cast<char*>(&tranforms_scale), 12);
		m_frame_position.push_back(tranforms_position);
		m_frame_rotate.push_back(tranforms_rotate);
		m_frame_scale.push_back(tranforms_scale);
	}

	// Anims
	file.seekg(ofs_anims);
	file.read(reinterpret_cast<char*>(&numloop), 4);

	int animoffset, animfps;
	for(int i=0; i<numloop; i++)
	{
		file.read(reinterpret_cast<char*>(&animoffset), 4);
		file.read(reinterpret_cast<char*>(&animfps), 4);
		m_anim_offset.push_back(animoffset);
		m_anim_fps.push_back(animfps);
	}

	file.close();

	return true;
}
