#pragma once

#include "ray.h"
#include "vector3d.h"
#include "interval.h"


namespace RayTracer
{


class Hittable
{
public:
	virtual ~Hittable() = default;

	struct HitRecord
	{
		Point3d point;
		Vector3d normal;
		double t;
		bool front_face;

		void SetFaceNormal(const Ray &ray, const Vector3d &outward_normal)
		{
			// outward_normal is assumed to be unit length
			
			front_face = ray.Direction().dot(outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};

	virtual bool Hit(const Ray &r, Interval t_int, HitRecord &record) const = 0;
};

}
