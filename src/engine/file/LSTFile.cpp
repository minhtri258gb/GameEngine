
#define IMPORT_ENGINE
#include "../../Main.h"

#include "../kernel/System.h"
extern System *g_pSystem;

#include "LSTFile.h"


LSTFile::LSTFile(string filename)
{
	idData = idPart = 0;

	load(filename);
}

LSTFile::~LSTFile()
{
}

bool LSTFile::next()
{
	if(idData >= listData.size())
		return false;

	string data = listData.at(idData);
	size_t pos = 0;
	string token;
	while((pos = data.find(" ")) != std::string::npos)
	{
		token = data.substr(0, pos);
		listPart.push_back(token);
		data.erase(0, pos + 1);
	}
	listPart.push_back(data);

	idPart = 0;
	idData++;

	return true;
}

string LSTFile::getString()
{
	if(idPart >= listPart.size())
		return "";
	return listPart.at(idPart++);
}

int LSTFile::getInt()
{
	if(idPart >= listPart.size())
		return 0;
	string data = listPart.at(idPart++);
	stringstream geek(data);
	int n;
	geek >> n;
	return n;
}

float LSTFile::getFloat()
{
	if(idPart >= listPart.size())
		return 0.0f;
	string data = listPart.at(idPart++);
	stringstream geek(data);
	float n;
	geek >> n;
	return n;
}

vec3 LSTFile::getVec3()
{
	if(idPart + 3 >= listPart.size())
		return vec3();

	vec3 value;
	string data = listPart.at(idPart++);
	stringstream geek(data);
	geek >> value.x;
	data = listPart.at(idPart++);
	geek = stringstream(data);
	geek >> value.y;
	data = listPart.at(idPart++);
	geek = stringstream(data);
	geek >> value.z;
	return value;
}

void LSTFile::load(string filename)
{
	ifstream fCFG;
	fCFG.open(filename.c_str(), ios::in);
	if(!fCFG.is_open())
	{
		g_pSystem->error("[LSTFile] Can't read file: " + filename);
		return;
	}

	string line;
	while(!fCFG.eof())
	{
		getline(fCFG, line);
		if(line.length() == 0 || line[0] == ';')
			continue;

		listData.push_back(line);
	}
	fCFG.close();
}
