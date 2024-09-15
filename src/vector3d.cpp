#include "vector3d.h"

namespace RayTracer
{

Vector3d Vector3d::Lerp(const Vector3d &a, const Vector3d &b, double t)
{
	if (t < 0)
		t = 0;
	else if (t > 1)
		t = 1;

	return a * (1.0 - t) + b * t;
}

}

