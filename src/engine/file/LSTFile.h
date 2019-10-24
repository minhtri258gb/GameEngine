#ifndef __LSTFILE_H__
#define __LSTFILE_H__

class LSTFile
{
public:

	// Constructor / Destructor
	LSTFile(string);
	~LSTFile();

	// General
	bool next();
	string getString();
	int getInt();
	float getFloat();
	vec3 getVec3();

private:

	// Variable
	vector<string> listData, listPart;
	unsigned int idData, idPart;

	// Change data
	void load(string);
};

#endif
