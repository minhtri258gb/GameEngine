
#include <glm/glm.hpp>

#define IMPORT_ENGINE
#include "../../Main.h"

#include "../kernel/System.h"
extern System *g_pSystem;

#include "BTFile.h"

BTFile::BTFile(string filename)
{
	load(filename);
}

BTFile::~BTFile()
{
	delete[] m_height;
}

int BTFile::getColumns()
{
	return this->m_columns;
}

int BTFile::getRows()
{
	return this->m_rows;
}

unsigned int BTFile::getData(int x, int y)
{
	return m_height[y * m_columns + x];
}

void BTFile::load(string filename)
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);

	if(!file.is_open())
	{
		g_pSystem->error("[BTFile] File not found: " + filename);
		return;
	}

	// Read header
	char marker[11];
	for(int i = 0; i < 10; i++)
		file.read(reinterpret_cast<char*>(&marker[i]), sizeof(char));
	marker[10] = '\0';

	if(string(marker) != "binterr1.3")
	{
		g_pSystem->error("[BTFile] File no support: " + filename);
		return;
	}

	file.read(reinterpret_cast<char*>(&m_columns), sizeof(int));
	file.read(reinterpret_cast<char*>(&m_rows), sizeof(int));
	file.read(reinterpret_cast<char*>(&m_datasize), sizeof(short));

	// Read content
	int arrSize = m_columns * m_rows;
	m_height = new float[arrSize];
	file.seekg(256);
	for(int i = 0; i < arrSize; i++)
		file.read(reinterpret_cast<char*>(&m_height[i]), m_datasize);

	file.close();

	// UPDATE MY FUNC
//	File* file = new File(filename, READ, BINARY);
//	if(file->check()) {
//		char marker[10];
//		for(int i=0; i<10; i++)
//			marker[i] = file->readByte();
//		*(&marker[0] + 10) = '\0';
//
//		if(String(marker) == "binterr1.3") {
//
//			short shorttemp;
//			float floattemp;
//			double doubletemp;
//
//			std::cout << file->readShort();
//
//	//		m_columns = file->readInt();
//	//		m_rows = file->readInt();
//	//		m_datasize = file->readShort();
//	//
//	//		std::cout << m_columns;
//
//	//		shorttemp = file->readShort(); // Floating-point flag
//	//		shorttemp = file->readShort(); // Horizontal units
//	//		shorttemp = file->readShort(); // UTM zone
//	//		shorttemp = file->readShort(); // Datum
//	//		doubletemp = file->readDouble(); // Left extent
//	//		doubletemp = file->readDouble(); // Right extent
//	//		doubletemp = file->readDouble(); // Bottom extent
//	//		doubletemp = file->readDouble(); // Top extent
//	//		shorttemp = file->readShort(); // External projection
//	//		floattemp = file->readShort(); // Scale (vertical units)
//
//			// Read content
//			int arrSize = m_columns * m_rows;
//			m_height = new float[arrSize];
//			file->position(256);
//			for(short i=0; i<arrSize; i++)
//				m_height[i] = file->readByte();
//
//		} else {
//			Log::console("File no support: " + filename.toCppStr());
//		}
//    } else {
//		Log::console("[error] Can't read file: " + filename);
////		game->exit();
//    }
//	delete file;
}
