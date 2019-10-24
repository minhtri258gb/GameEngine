#ifndef __MTMDFILE_H__
#define __MTMDFILE_H__


class MTMDFile
{
public:

	// Variable
	string m_filedir;
	vector<vec3> m_vertices;
	vector<vec3> m_normals;
	vector<vec2> m_uvs;
	vector<ivec3> m_idbone;
	vector<unsigned int> m_indices;
	vector<vec3> m_weight;
	vector<int> m_meshs_offset;
	vector<string> m_meshs_materials;
	vector<string> m_bones_name;
	vector<int> m_bones_parent;
	vector<vec3> m_frame_position;
	vector<vec4> m_frame_rotate;
	vector<vec3> m_frame_scale;
	vector<int> m_anim_offset, m_anim_fps;

	// Constructor / Destructor
	MTMDFile();
	~MTMDFile();

	// Change data
	bool load(string filepath);

};

#endif
