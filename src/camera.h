#pragma once

#include <cstddef>

#include "color.h"
#include "image.h"
#include "ray.h"
#include "vector3d.h"
#include "hittable_list.h"


namespace RayTracer
{

class Camera {
public:
	Camera() {}

	void SetScene(const HittableList &scene) { m_scene = scene; }
	// force_initialize will initialize the camera again even if it's already
	// been initialized.
	void Render(bool force_initialize = false);
	void Save(std::filesystem::path filepath) const;

	size_t image_width = 100;
	double aspect_ratio = 1.0;
	size_t samples_per_pixel = 10;
	bool verbose = false;
	size_t max_bounces = 10;
    double vfov = 90;  // Vertical field of view, in degrees
    Point3d look_from = Point3d{0, 0, 0};
    Point3d look_at = Point3d{0, 0, -1};
    Vector3d v_up = Vector3d{0, 1, 0};

private:
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

    // Camera frame basis vectors
	Vector3d m_origin;
    Vector3d m_u;
    Vector3d m_v;
    Vector3d m_w;

	double m_focal_length;
	
	HittableList m_scene;
	// The minimum distance from the surface a point has to be to be considered
	// for a bounce
	double m_min_distance_from_surface = 0.001;

	Vector3d SampleSquare() const
	{
		return Vector3d(
			Utility::random_double() - 0.5, 
			Utility::random_double() - 0.5, 
			0
		);
	}
	Ray GetRay(size_t x, size_t y) const;
	RGB GetRayColor(const Ray& ray, int depth) const;

	bool m_is_initialized = false;
	void Initialize(bool force_initialize = false);
};

}
