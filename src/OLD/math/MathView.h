#ifndef MATHVIEW_H
#define MATHVIEW_H


class MathView
{
public:
	static vec3 movement(vec3 velocity, vec3 vecdir, float speed, float max_speed, bool yMovement);
};

#endif
