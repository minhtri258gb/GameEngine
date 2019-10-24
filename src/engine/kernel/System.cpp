
#include <ctime>

#define IMPORT_ENGINE
#include "../../Main.h"

#include "System.h"


System::System()
{
	remove("doc/runtime.log");

	m_mainloop = true;
	rd = std::mt19937(time(NULL));
}

void System::init()
{
	world.init();
	audio.init();
	network.init();
}

System::~System()
{

}

void System::log(string message)
{
	ofstream f;
	f.open("doc/runtime.log", ios::out | ios::app);
	f << message;
	f.close();
}

void System::error(string message)
{
	MessageBox(NULL, message.c_str(), "Error", MB_SYSTEMMODAL | MB_ICONERROR);
	m_mainloop = false;
}

bool System::probability(unsigned int n)
{
	return (rd() % 100 < n);
}

unsigned int System::rand(unsigned int n)
{
	return rd() % n;
}

int System::range(int d, int c)
{
	return rd()%(c-d+1)+d;
}

bool System::isRun()
{
	return m_mainloop;
}

void System::exit()
{
	m_mainloop = false;
}
