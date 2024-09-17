#include <cstddef>
#include <memory>

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vector3d.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"

using namespace RayTracer;


void Run(size_t image_width)
{
    auto material_ground = std::make_shared<Lambertian>(RGB{0.8, 0.8, 0.0});
    auto material_center = std::make_shared<Lambertian>(RGB{0.1, 0.2, 0.5});
    auto material_left = std::make_shared<Dielectric>(1.5);
    auto material_bubble = std::make_shared<Dielectric>(1.0 / 1.5);
    auto material_right = std::make_shared<Metal>(RGB{0.8, 0.6, 0.2}, 1.0);

	HittableList scene;
	scene.Add(std::make_shared<Sphere>(Point3d{0, -100.5, -1.0}, 100, material_ground));
	scene.Add(std::make_shared<Sphere>(Point3d{0, 0, -1.2}, 0.5, material_center));
	scene.Add(std::make_shared<Sphere>(Point3d{-1, 0, -1}, 0.5, material_left));
	scene.Add(std::make_shared<Sphere>(Point3d{-1, 0, -1}, 0.4, material_bubble));
	scene.Add(std::make_shared<Sphere>(Point3d{1, 0, -1}, 0.5, material_right));

	Camera cam;
	cam.image_width = image_width;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.origin = Vector3d(0, 0, 0);
	cam.samples_per_pixel = 30;
	cam.max_bounces = 10;
	cam.verbose = true;
	cam.SetScene(scene);
	cam.Render();
	cam.Save("output.png");
	cam.Save("output.ppm");
}

int main() 
{
	Run(400);
	return 0;
}
