
#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../kernel/System.h"
extern System *g_pSystem;

#include "Network.h"

#define APP_PORT 4294
#define MAX_CLIENT 32

Network::Network() {
	host = NULL;
	peer = NULL;
	isServer = true;
}

Network::~Network() {
	if(host) enet_host_destroy(host);

	enet_deinitialize();
}

void Network::init() {

	if(enet_initialize() != 0) {
		g_pSystem->error("[Network] An error occurred while initializing ENet.");
		return;
	}
	atexit(enet_deinitialize);

	if(isServer) {
		ENetAddress address;
		address.host = ENET_HOST_ANY;
		address.port = APP_PORT;

		host = enet_host_create(& address	/* the address to bind the server host to */,
								MAX_CLIENT	/* allow up to 32 clients and/or outgoing connections */,
								2			/* allow up to 2 channels to be used, 0 and 1 */,
								0			/* assume any amount of incoming bandwidth */,
								0			/* assume any amount of outgoing bandwidth */);
		if(!host) {
			g_pSystem->error("[Network] An error occurred while trying to create an ENet host.");
			return;
		}
	} else { // client
		host = enet_host_create(NULL		/* create a client host */,
								1			/* only allow 1 outgoing connection */,
								2			/* allow up 2 channels to be used, 0 and 1 */,
								0			/* assume any amount of incoming bandwidth */,
								0			/* assume any amount of outgoing bandwidth */);
		if(!host) {
			g_pSystem->error("[Network] An error occurred while trying to create an ENet host.");
			return;
		}

		ENetAddress address;
		enet_address_set_host(&address, "localhost");
		address.port = APP_PORT;

		peer = enet_host_connect(host, &address, 2, 0);
		if(!peer) {
			g_pSystem->error("[Network] No available peers for initializing an ENet connection");
			return;
		}
	}
}

void Network::update() {
	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while(enet_host_service(host, & event, 1000) > 0) {
		switch(event.type) {
		case ENET_EVENT_TYPE_NONE:
			break;
		case ENET_EVENT_TYPE_CONNECT:
			std::cout << "A new client connected from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
			/* Store any relevant client information here. */
//			char datainfo[20] = "Client information";
//			event.peer->data = &datainfo;
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			std::cout << "A packet of length " << event.packet->dataLength << " containing " <<
				event.packet->data << " was received from " << event.peer->data << " on channel " << event.channelID << ".\n";
			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy (event.packet);
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << event.peer->data << " disconnected.\n";
			/* Reset the peer's client information. */
			event.peer->data = NULL;
	    }
	}
}

void Network::send(string message) {
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket * packet = enet_packet_create(message.c_str(), message.length() + 1, ENET_PACKET_FLAG_RELIABLE);
	/* Extend the packet so and append the string "foo", so it now */
	/* contains "packetfoo\0"                                      */
	enet_packet_resize(packet, message.length() + 1);
	memcpy(packet->data, message.c_str(), message.length());
	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */
	enet_peer_send(peer, 0, packet);
//	...
//	...
//	...
//	/* One could just use enet_host_service() instead. */
//	enet_host_flush (host);
}

//disconnect() {
//	ENetEvent event;
//	enet_peer_disconnect (peer, 0);
//	/* Allow up to 3 seconds for the disconnect to succeed
//	 * and drop any packets received packets.
//	 */
//	while (enet_host_service (client, & event, 3000) > 0)
//	{
//	    switch (event.type)
//	    {
//	    case ENET_EVENT_TYPE_RECEIVE:
//	        enet_packet_destroy (event.packet);
//	        break;
//	    case ENET_EVENT_TYPE_DISCONNECT:
//	        puts ("Disconnection succeeded.");
//	        return;
//	    ...
//	    ...
//	    ...
//	    }
//	}
//	/* We've arrived here, so the disconnect attempt didn't */
//	/* succeed yet.  Force the connection down.             */
//	enet_peer_reset (peer);
//	...
//	...
//	...
//}

//connect() {
//	ENetAddress address;
//	ENetEvent event;
//	ENetPeer *peer;
//	/* Connect to some.server.net:1234. */
//	enet_address_set_host (& address, "some.server.net");
//	address.port = 1234;
//	/* Initiate the connection, allocating the two channels 0 and 1. */
//	peer = enet_host_connect (client, & address, 2, 0);
//	if (peer == NULL)
//	{
//	   fprintf (stderr,
//	            "No available peers for initiating an ENet connection.\n");
//	   exit (EXIT_FAILURE);
//	}
//	/* Wait up to 5 seconds for the connection attempt to succeed. */
//	if (enet_host_service (client, & event, 5000) > 0 &&
//	    event.type == ENET_EVENT_TYPE_CONNECT)
//	{
//	    puts ("Connection to some.server.net:1234 succeeded.");
//	    ...
//	    ...
//	    ...
//	}
//	else
//	{
//	    /* Either the 5 seconds are up or a disconnect event was */
//	    /* received. Reset the peer in the event the 5 seconds   */
//	    /* had run out without any significant event.            */
//	    enet_peer_reset (peer);
//	    puts ("Connection to some.server.net:1234 failed.");
//	}
//	...
//	...
//	...
//}
