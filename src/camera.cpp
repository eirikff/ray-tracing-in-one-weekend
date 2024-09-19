#include "camera.h"
#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "color.h"
#include "vector3d.h"
#include "utility.h"
#include "material/material.h"

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

    m_origin = look_from;

    double theta = Utility::deg2rad(vfov);
    double h = std::tan(theta / 2);
	m_viewport_height = 2 * h * focus_distance;
	m_viewport_width = (m_viewport_height * image_width) / m_image_height;

    m_w = (look_from - look_at).Unit();
    m_u = v_up.cross(m_w).Unit();
    m_v = m_w.cross(m_u);
	
	m_viewport_u = m_viewport_width * m_u;
	m_viewport_v = m_viewport_height * -m_v;
	m_viewport_upper_left = m_origin 
							- focus_distance * m_w
							- m_viewport_u / 2 
							- m_viewport_v / 2;

    double defocus_radius = focus_distance * std::tan(Utility::deg2rad(defocus_angle / 2));
    m_defocus_disk_u = defocus_radius * m_u;
    m_defocus_disk_v = defocus_radius * m_v;

	m_pixel_delta_u = m_viewport_u / image_width;
	m_pixel_delta_v = m_viewport_v / m_image_height;
	m_pixel_00 = m_viewport_upper_left 
				 + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);

	m_image = Image(image_width, m_image_height);

	m_is_initialized = true;

    if (verbose)
    {
        std::clog << "Camera parameters:"
            << "\n- Image size (w x h) [px]: " << image_width << " x " << m_image_height 
            << "\n  - Desired aspect ratio: " << aspect_ratio 
            << "\n  - Actual aspect ratio:  " << double(image_width) / m_image_height
            << "\n- Viewport size (w x h): " << m_viewport_width << " x " << m_viewport_height
            << "\n  - Viewport u: " << m_viewport_u
            << "\n  - Viewport v: " << m_viewport_v
            << "\n  - Pixel delta u: " << m_pixel_delta_u
            << "\n  - Pixel delta v: " << m_pixel_delta_v
            << "\n- Vertical FOV [deg]: " << vfov 
            << "\n- Focus distance: " << focus_distance
            << "\n- Defocus blur"
            << "\n  - Angle [deg]: " << defocus_angle
            << "\n  - Radius: " << defocus_radius
            << "\n  - disk_u: " << m_defocus_disk_u
            << "\n  - disk_v: " << m_defocus_disk_v
            << "\n- Camera frame"
            << "\n  - Look from: " << look_from 
            << "\n  - Look at:   " << look_at
            << "\n  - Up vector: " << v_up
            << "\n  - Axes"
            << "\n    - u (right): " << m_u
            << "\n    - v (up):    " << m_v
            << "\n    - w (away):  " << m_w
            << std::endl;
    }
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
        Ray scattered;
        RGB attenuation;
        if (record.material->Scatter(r, record, attenuation, scattered))
        {
            return attenuation * GetRayColor(scattered, depth - 1);
        }
        return RGB{0, 0, 0};
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
    auto ray_origin = (defocus_angle <= 0) ? m_origin : DefocusDiskSample();
	auto ray_direction = pixel_sample - ray_origin;

	return Ray(ray_origin, ray_direction);
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
	m_image.ApplyGamma(2);

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
