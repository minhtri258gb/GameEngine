
#define DEBUG 1

#define IMPORT_ENGINE
#include "../../../Main.h"

#include "../../../engine/kernel/Timer.h"
extern Timer *g_pTimer;

#include "../../../engine/kernel/View.h"
extern View *g_pView;

#include "../../../OLD/math/MathView.h"
#include "MainPlayer.h"

#define SPEED_WALK 50.0f
#define SPEED_RUN 5200.0f
#define MAXSPEEDMOVE 8000.0f
#define EYEHIGHT 64.0f
#define RANGE_USE 64.0f

#if DEBUG
bool debugnoclip = false;
#endif // DEBUG


MainPlayer::MainPlayer()
{
	body = new ControlBody();

    vecFront = vec3(0.0f, 0.0f, -1.0f);
    vecRight = vec3(1.0f, 0.0f, 0.0f);
    angle = 0.0f;
    sprint = false;
}

MainPlayer::~MainPlayer()
{
	delete body;
}

void MainPlayer::init()
{
	body->loadCapsule(origin);

	if(debugnoclip)
		body->setGravity(0.0f);
}

void MainPlayer::update()
{
	origin = body->getOrigin();
	g_pView->setPosition(vec3(origin.x, origin.y + 40.0f, origin.z)); // 24 + 40 = 64 / 68

	vecFront = g_pView->getVeclook();

	vecRight = cross(vecFront, vec3(0,1,0));
	normalize(vecRight);

	// Velocity
	if(abs(velocity.x) < 0.1f && abs(velocity.y) < 0.1f && abs(velocity.z) < 0.1f)
		velocity = vec3();
	else
		velocity *= 0.8f;

	#if DEBUG
//	body->setVelocity(velocity * engine.timer->getTimePassed());
	body->setWalkDirection(velocity * g_pTimer->getTimePassed());
	#else
	body->setWalkDirection(velocity * engine.kernel.timer.getTimePassed());
	#endif // DEBUG

//	sprint = false;
}

void MainPlayer::move(int direct)
{
	float speed;
	if(sprint) speed = SPEED_RUN;
	else speed = SPEED_WALK;

	switch(direct)
	{
		case 1: velocity = MathView::movement(velocity, vecFront,  speed, MAXSPEEDMOVE, debugnoclip); break;
		case 2: velocity = MathView::movement(velocity, vecFront, -speed, MAXSPEEDMOVE, debugnoclip); break;
		case 3: velocity = MathView::movement(velocity, vecRight, -speed, MAXSPEEDMOVE, debugnoclip); break;
		case 4: velocity = MathView::movement(velocity, vecRight,  speed, MAXSPEEDMOVE, debugnoclip); break;
	}
}

void MainPlayer::jump()
{
	body->jump(512.0f);
}

void MainPlayer::use()
{
//	void* pUser = NULL;
//
//	Vec3 end = origin + vecFront * RANGE_USE;
//    if(engine.world->raycast(origin, end, pUser)) {
//		MyEntity* pMyEntity = NULL;
//		if(pUser != NULL) {
//			pMyEntity = (MyEntity*)pUser;
//			pMyEntity->model->force(Vec3(0, 1000, 0));
//		}
//    }
}

void MainPlayer::noclip()
{
    if(debugnoclip) {
		body->setGravity(1024.0f);
    } else {
		body->setGravity(0.0f);
    }
    debugnoclip = !debugnoclip;
}

vec3 MainPlayer::getOrigin()
{
	return origin;
}

void MainPlayer::setOrigin(vec3 origin)
{
	this->origin = origin;
}

void MainPlayer::setSprint(bool toogle)
{
    this->sprint = toogle;
}

bool MainPlayer::onGround()
{
	return body->onGround();
}

void cmd_forward()
{
	engine.m_mainPlayer->move(1);
}

void cmd_back()
{
	engine.m_mainPlayer->move(2);
}

void cmd_moveleft()
{
	engine.m_mainPlayer->move(3);
}

void cmd_moveright()
{
	engine.m_mainPlayer->move(4);
}

void cmd_jump()
{
	engine.m_mainPlayer->jump();
}

void cmd_sprint()
{
	engine.m_mainPlayer->setSprint(true);
}

void cmd_use()
{
	engine.m_mainPlayer->use();
}

void cmd_debugnoclip()
{
	engine.m_mainPlayer->noclip();
}
