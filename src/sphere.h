#pragma once

#include <cmath>

#include "vector3d.h"
#include "hittable.h"


namespace RayTracer
{

class Sphere : public Hittable
{
public:
	Sphere(const Point3d &center, double radius)
	: m_center(center), m_radius(std::fmax(0, radius))
	{}

	virtual bool Hit(const Ray &r, Interval t_int, HitRecord &record) const override;

private:
	Point3d m_center;
	double m_radius;
};

}
