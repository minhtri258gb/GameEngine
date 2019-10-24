
#include "../../Main.h"
#include "MathView.h"


vec3 MathView::movement(vec3 velocity, vec3 vecdir, float speed, float max_speed, bool yMovement)
{

	vec3 newVelocity = vecdir;

	if (!yMovement)
	{
		newVelocity.y = 0;
		normalize(newVelocity);
	}

	newVelocity *= speed;

	newVelocity.x += velocity.x;
	newVelocity.z += velocity.z;

	if (yMovement)
		newVelocity.y += velocity.y;
	else
		newVelocity.y = velocity.y;

	float lenghtspeed = newVelocity.length();
	if (lenghtspeed > max_speed)
	{
		newVelocity *= (max_speed / lenghtspeed);
	}
	return newVelocity;
}
