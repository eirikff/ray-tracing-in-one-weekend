#include "hittable_list.h"
#include "interval.h"


namespace RayTracer
{

bool HittableList::Hit(const Ray &r, Interval t_int, HitRecord &record) const
{
	HitRecord temp_record;
	bool hit_anything = false;
	double closest_so_far = t_int.Max();

	for (const auto &object : m_objects)
	{
		if (object->Hit(r, Interval(t_int.Min(), closest_so_far), temp_record))
		{
			hit_anything = true;
			closest_so_far = temp_record.t;
			record = temp_record;
		}
	}

	return hit_anything;
}

}
