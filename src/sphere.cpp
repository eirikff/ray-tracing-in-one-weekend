#include "sphere.h"
#include <cstdlib>

namespace RayTracer
{

bool Sphere::Hit(const Ray &r, double ray_tmin, double ray_tmax, 
				 HitRecord &record) const
{
	Vector3d cq = m_center - r.Origin();
	double a = r.Direction().LengthSquared();  // d.dot(d)
	double h = r.Direction().dot(cq);
	double c = cq.LengthSquared() - m_radius * m_radius;
	double discriminant = h*h - a*c;

	if (discriminant < 0)
	{
		return false;
	}


	double sqrtd = std::sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range
	double root = (h - sqrtd) / a;
	if (root <= ray_tmin || root >= ray_tmax)
	{
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || root >= ray_tmax)
		{
			return false;
		}
	}

	record.t = root;
	record.point = r.At(record.t);
	Vector3d outward_normal = (record.point - m_center) / m_radius;
	record.SetFaceNormal(r, outward_normal);

	return true;
}

}
