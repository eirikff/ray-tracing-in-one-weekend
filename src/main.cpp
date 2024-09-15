#include <cstddef>
#include <memory>

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vector3d.h"

using namespace RayTracer;


void Run(size_t image_width)
{
	double aspect_ratio = 16.0 / 9.0;

	size_t image_height = int(image_width / aspect_ratio);
	// Make sure height is at least 1
	image_height = (image_height < 1) ? 1 : image_height;

	double viewport_height = 2.0;
	double viewport_width = (viewport_height * image_width) / image_height;

	double focal_length = 1;
	Vector3d origin{0, 0, 0};

	HittableList scene;
	scene.Add(std::make_shared<Sphere>(Point3d{0, 0, -1}, 0.5));
	scene.Add(std::make_shared<Sphere>(Point3d{0, -100.5, -1}, 100));

	Camera cam{
		image_width, image_height, 
		viewport_width, viewport_height,
		focal_length, origin
	};
	cam.SetScene(scene);
	cam.Render();
	cam.Save("output.ppm");
}

int main() 
{
	Run(600);
	return 0;
}
