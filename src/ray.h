#pragma once

#include "vector3d.h"
#include "color.h"


namespace RayTracer
{

class Ray 
{
public:
	Ray() : m_color(0, 0, 0) { }
	Ray(const Vector3d &origin, const Vector3d &direction)
	: m_origin(origin), m_direction(direction.Unit()), m_color(0, 0, 0)
	{ }
	Ray(const Vector3d &origin, const Vector3d &direction, const RGB &color)
	: m_origin(origin), m_direction(direction.Unit()), m_color(color)
	{ }

	const Point3d &Origin() const { return m_origin; }
	const Vector3d &Direction() const { return m_direction; }
	const RGB &Color() const { return m_color; }

	Vector3d At(double t) const { return m_origin + t * m_direction; }

private:
	Point3d m_origin;
	Vector3d m_direction;
	RGB m_color;

};

}
