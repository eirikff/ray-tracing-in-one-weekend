#include <cstddef>
#include <memory>

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vector3d.h"

using namespace RayTracer;


void Run(size_t image_width)
{
	HittableList scene;
	scene.Add(std::make_shared<Sphere>(Point3d{0, 0, -1}, 0.5));
	scene.Add(std::make_shared<Sphere>(Point3d{0, -100.5, -1}, 100));

	Camera cam;
	cam.image_width = image_width;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.origin = Vector3d(0, 0, 0);
	cam.samples_per_pixel = 50;
	cam.verbose = true;
	cam.SetScene(scene);
	cam.Render();
	cam.Save("output.png");
}

int main() 
{
	Run(600);
	return 0;
}
