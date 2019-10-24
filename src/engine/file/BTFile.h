#ifndef BTFILE_H
#define BTFILE_H


class BTFile {
public:

	// Constructor
	BTFile(string filename);
	~BTFile();

	// General
	int getColumns();
	int getRows();
	unsigned int getData(int x, int y);

protected:

private:

	// Variable
	int m_columns, m_rows;
	short m_datasize;
	float* m_height;

	// General
	void load(string filename);
};

#endif
