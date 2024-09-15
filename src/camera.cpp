#include "camera.h"
#include "hittable.h"
#include "ray.h"
#include "color.h"
#include "vector3d.h"
#include "utility.h"

#include <cmath>
#include <iostream>

namespace RayTracer
{

RGB GetBackgroundColor(const Ray &r)
{
	RGB white{1, 1, 1};
	RGB blue{0.5, 0.7, 1};
	
	double t = 0.5 * (r.Direction().y() + 1);
	return Vector3d::Lerp(white, blue, t);
}


RGB GetRayColor(const Ray &r, const HittableList &scene)
{
	Hittable::HitRecord record;
	if (scene.Hit(r, 0, Constants::Infinity, record))
	{
		return 0.5 * (record.normal + RGB{1, 1, 1});
	}

	return GetBackgroundColor(r);
}

void Camera::Render()
{
	for (size_t y = 0; y < m_image_height; y++)
	{
		for (size_t x = 0; x < m_image_width; x++)
		{
			auto pixel_center = m_pixel_00 + x*m_pixel_delta_u + y*m_pixel_delta_v;
			auto ray_direction = pixel_center - m_origin;
			Ray r(m_origin, ray_direction);

			RGB pixel_color = GetRayColor(r, m_scene);
			m_image(x, y) = pixel_color.Uint8();
		}
	}
}

void Camera::Save(std::filesystem::path filepath) const
{
	int bytes = m_image.ToFile(filepath);
	std::cout << "Successfully wrote " << bytes << " bytes to " 
		<< filepath << std::endl;
}

}
