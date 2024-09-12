#pragma once

#include "vector3d.h"


namespace RayTracer
{

class Ray 
{
public:
	Ray() { }
	Ray(const Vector3d &origin, const Vector3d &direction)
	: m_origin(origin), m_direction(direction)
	{ }

	const Point3d &Origin() const { return m_origin; }
	const Vector3d &Direction() const { return m_direction; }

	Vector3d At(double t) const { return m_origin + t * m_direction; }

private:
	Point3d m_origin;
	Vector3d m_direction;

};

}
