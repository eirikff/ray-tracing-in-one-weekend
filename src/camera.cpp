#include "camera.h"
#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "color.h"
#include "vector3d.h"
#include "utility.h"

#include <chrono>
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

RGB Camera::GetRayColor(const Ray &r, int depth) const
{
	// At the maxium depth/number of bounces, no more light is emitted (i.e. black)
	if (depth <= 0)
	{
		return RGB{0, 0, 0};
	}

	Hittable::HitRecord record;
	if (m_scene.Hit(r, Interval(m_min_distance_from_surface, Constants::Infinity), record))
	{
		// return 0.5 * (record.normal + RGB{1, 1, 1});
		Vector3d direction = Vector3d::RandomOnHemisphere(record.normal);
		return 0.5 * GetRayColor(Ray(record.point, direction), depth - 1);
	}

	// Make background gradient
	RGB white{1, 1, 1};
	RGB blue{0.5, 0.7, 1};
	
	double t = 0.5 * (r.Direction().y() + 1);
	return Vector3d::Lerp(white, blue, t);
}

Ray Camera::GetRay(size_t x, size_t y) const
{
	Vector3d offset = SampleSquare();

	auto pixel_sample = m_pixel_00 
						+ (x + offset.x()) * m_pixel_delta_u 
						+ (y + offset.y()) * m_pixel_delta_v;
	auto ray_direction = pixel_sample - origin;

	return Ray(origin, ray_direction);
}

void Camera::Render(bool force_initialize)
{
	Initialize(force_initialize);

	auto start = std::chrono::high_resolution_clock::now();
	for (size_t y = 0; y < m_image_height; y++)
	{
		if (verbose)
		{
			std::clog << "\rScanlines completed: " << y << "/" 
					  << m_image_height << "   " << std::flush;
		}

		for (size_t x = 0; x < image_width; x++)
		{
			RGB pixel_color{0, 0, 0};
			for (size_t s = 0; s < samples_per_pixel; s++)
			{
				Ray r = GetRay(x, y);
				RGB sampled_color = GetRayColor(r, max_bounces);
				pixel_color += sampled_color;
			}
			m_image(x, y) = pixel_color / samples_per_pixel;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = end - start;
	if (verbose)
	{
		std::clog << "\rDone. Time used: " 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.0 
			<< " seconds.                   " << std::endl;
	}
}

void Camera::Save(std::filesystem::path filepath) const
{
	if (filepath.extension() == ".ppm")
	{
		int bytes = m_image.SaveAsPPM(filepath);
		std::cout << "Successfully wrote " << bytes << " bytes to " 
			<< filepath << std::endl;
	}
	else if (filepath.extension() == ".png")
	{
		m_image.SaveAsPNG(filepath);
		std::cout << "Successfully wrote to " 
			<< filepath << std::endl;
	}
	else 
	{
		std::cout << "File extension " << filepath.extension() 
			<< " is not supported" << std::endl;
	}
}

}
