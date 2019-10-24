#ifndef __MAINPLAYER_H__
#define __MAINPLAYER_H__

#include "../../../engine/kernel/View.h"
#include "../../../OLD/physic/component/ControlBody.h"


class MainPlayer
{
public:

	// Constructor
	MainPlayer();
	~MainPlayer();

	// General
	void init();
	void update();
	void camMove(int direct);

	// Event
	void move(int direct);
	void jump();
	void use();
	void noclip();

	// Get / Set
	vec3 getOrigin();
	void setOrigin(vec3);
	void setSprint(bool);

	// Check
	bool onGround();

private:

	// Variable
	ControlBody* body;
	vec3 origin;
    vec3 vecFront, vecRight;
    vec3 velocity;
	float angle;
	bool sprint;

};

#endif
