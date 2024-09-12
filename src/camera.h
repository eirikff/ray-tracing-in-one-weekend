#pragma once

#include <cstddef>

#include "image.h"
#include "vector3d.h"


namespace RayTracer
{

class Camera {
public:
	Camera(size_t image_width, size_t image_height, 
		   double viewport_width, double viewport_height,
		   double focal_length, const Point3d &origin)
	: m_image_width(image_width), m_image_height(image_height),
	  m_image(image_width, image_height),
	  m_viewport_width(viewport_width), m_viewport_height(viewport_height),
	  m_viewport_u{viewport_width, 0, 0}, m_viewport_v{0, -viewport_height, 0},
	  m_pixel_delta_u(m_viewport_u / image_width), 
	  m_pixel_delta_v(m_viewport_v / image_height),
	  m_focal_length(focal_length), m_origin(origin)
	{ 
		m_viewport_upper_left = origin 
								- Vector3d(0, 0, m_focal_length)
								- m_viewport_u / 2 
								- m_viewport_v / 2;

		m_pixel_00 = m_viewport_upper_left 
					 + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);
	}

	void Render();
	void Save(std::filesystem::path filepath) const;

private:
	size_t m_image_width;
	size_t m_image_height;
	Image m_image;

	double m_viewport_width;
	double m_viewport_height;
	Vector3d m_viewport_u;
	Vector3d m_viewport_v;
	Vector3d m_viewport_upper_left;
	Vector3d m_pixel_00;
	Vector3d m_pixel_delta_u;
	Vector3d m_pixel_delta_v;

	double m_focal_length;
	Vector3d m_origin;
	
};

}
