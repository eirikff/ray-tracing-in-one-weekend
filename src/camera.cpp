#include "camera.h"
#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "color.h"
#include "vector3d.h"
#include "utility.h"

#include <cmath>
#include <iostream>

namespace RayTracer
{

void Camera::Initialize(bool force_initialize)
{
	if (m_is_initialized && !force_initialize)
		return;

	m_image_height = int(image_width / aspect_ratio);
	// Make sure height is at least 1
	m_image_height = (m_image_height < 1) ? 1 : m_image_height;

	// TODO: should focal length be a public parameter
	m_focal_length = 1;

	// TODO: should viewport height/width be a public parameter?
	// TODO: viewport calculation should use FOV parameter
	m_viewport_height = 2.0;
	m_viewport_width = (m_viewport_height * image_width) / m_image_height;
	
	m_viewport_u = Vector3d(m_viewport_width, 0, 0);
	m_viewport_v = Vector3d(0, -m_viewport_height, 0);
	m_viewport_upper_left = origin 
							- Vector3d(0, 0, m_focal_length)
							- m_viewport_u / 2 
							- m_viewport_v / 2;


	m_pixel_delta_u = m_viewport_u / image_width;
	m_pixel_delta_v = m_viewport_v / m_image_height;
	m_pixel_00 = m_viewport_upper_left 
				 + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);

	m_image = Image(image_width, m_image_height);

	m_is_initialized = true;
}

RGB Camera::GetRayColor(const Ray &r) const
{
	Hittable::HitRecord record;
	if (m_scene.Hit(r, Interval(0, Constants::Infinity), record))
	{
		return 0.5 * (record.normal + RGB{1, 1, 1});
	}

	// Make background gradient
	RGB white{1, 1, 1};
	RGB blue{0.5, 0.7, 1};
	
	double t = 0.5 * (r.Direction().y() + 1);
	return Vector3d::Lerp(white, blue, t);
}

void Camera::Render(bool force_initialize)
{
	Initialize(force_initialize);

	for (size_t y = 0; y < m_image_height; y++)
	{
		for (size_t x = 0; x < image_width; x++)
		{
			auto pixel_center = m_pixel_00 + x*m_pixel_delta_u + y*m_pixel_delta_v;
			auto ray_direction = pixel_center - origin;
			Ray r(origin, ray_direction);

			RGB pixel_color = GetRayColor(r);
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
