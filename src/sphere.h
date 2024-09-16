#pragma once

#include <cmath>
#include <memory>

#include "vector3d.h"
#include "hittable.h"
#include "material/material.h"


namespace RayTracer
{

class Sphere : public Hittable
{
public:
	Sphere(const Point3d &center, double radius, std::shared_ptr<Material> material)
	: m_center(center), m_radius(std::fmax(0, radius)), m_material(material)
	{}

	virtual bool Hit(const Ray &r, Interval t_int, HitRecord &record) const override;

private:
	Point3d m_center;
	double m_radius;
    std::shared_ptr<Material> m_material;
};

}
