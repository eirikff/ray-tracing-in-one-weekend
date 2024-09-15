#include "hittable_list.h"


namespace RayTracer
{

bool HittableList::Hit(const Ray &r, double ray_tmin, double ray_tmax, 
				       HitRecord &record) const
{
	HitRecord temp_record;
	bool hit_anything = false;
	double closest_so_far = ray_tmax;

	for (const auto &object : m_objects)
	{
		if (object->Hit(r, ray_tmin, closest_so_far, temp_record))
		{
			hit_anything = true;
			closest_so_far = temp_record.t;
			record = temp_record;
		}
	}

	return hit_anything;
}

}
