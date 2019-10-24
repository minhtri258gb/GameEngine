#ifndef NETWORK_H
#define NETWORK_H

#include <enet/enet.h>


class Network {
public:

	// Constructor
	Network();
	~Network();

	// General
	void init();
	void update();

	// Event
	void send(string);

private:

	// Variable
	ENetHost* host;
	ENetPeer* peer;
	bool isServer;
};

#endif
