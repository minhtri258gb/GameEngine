
#include "../../Main.h"
#include "Math.h"


mat4 Math::viewmodel(mat4 view, vec3 pos, float scale)
{
	mat4 modelview;
	modelview[0][0] = scale;
	modelview[1][1] = scale;
	modelview[2][2] = scale;

	modelview[0][3] = view[0][3];
	modelview[1][3] = view[1][3];
	modelview[2][3] = view[2][3];
	modelview[3][0] = view[0][0] * pos.x + view[1][0] * pos.y + view[2][0] * pos.z + view[3][0];
	modelview[3][1] = view[0][1] * pos.x + view[1][1] * pos.y + view[2][1] * pos.z + view[3][1];
	modelview[3][2] = view[0][2] * pos.x + view[1][2] * pos.y + view[2][2] * pos.z + view[3][2];
	modelview[3][3] = view[0][3] * pos.x + view[1][3] * pos.y + view[2][3] * pos.z + view[3][3];

	return modelview;
}
