#ifndef __COMMAND_H__
#define __COMMAND_H__

typedef void (*pFuncCMD)();


class Command
{
public:

	// Constructor
	Command();
	~Command();

	// Framework
	void update();

	// General
	void keyPress(int idkey, bool state);

	// Change data
	void keyBind(string key, string func);

private:

	// Variable
	vector<pFuncCMD> m_listCMD;
	bitset<354> m_keyAction;
	bitset<354> m_keyLoop;

	// Get / Set
	int convertKey(string key);
	pFuncCMD convertFunction(string command);
};

#endif
