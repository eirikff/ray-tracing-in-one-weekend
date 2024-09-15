#pragma once

#include "hittable.h"
#include "ray.h"

#include <memory>
#include <vector>


namespace RayTracer
{

class HittableList : public Hittable
{
public:
	HittableList() {}

	void Clear() { m_objects.clear(); }
	void Add(std::shared_ptr<Hittable> object)
	{
		m_objects.push_back(object);
	}

	virtual bool Hit(const Ray &r, double ray_tmin, double ray_tmax, 
				     HitRecord &record) const;

private:
	std::vector<std::shared_ptr<Hittable>> m_objects;
};

}
