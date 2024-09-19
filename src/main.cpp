#include <cmath>
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


void ManySpheres() 
{
    HittableList scene;

    auto ground_material = std::make_shared<Lambertian>(RGB(0.5, 0.5, 0.5));
    scene.Add(std::make_shared<Sphere>(Point3d(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = Utility::random_double();
            Point3d center{
                a + 0.9*Utility::random_double(), 
                0.2, 
                b + 0.9*Utility::random_double()
            };

            if ((center - Point3d(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = RGB::Random() * RGB::Random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    scene.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = RGB::Random(0.5, 1);
                    auto fuzz = Utility::random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    scene.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    scene.Add(std::make_shared<Sphere>(Point3d(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(RGB(0.4, 0.2, 0.1));
    scene.Add(std::make_shared<Sphere>(Point3d(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(RGB(0.7, 0.6, 0.5), 0.0);
    scene.Add(std::make_shared<Sphere>(Point3d(4, 1, 0), 1.0, material3));

	Camera cam;
	cam.image_width = 1200;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.samples_per_pixel = 500;
	cam.max_bounces = 50;
	cam.verbose = true;

    cam.vfov     = 20;
    cam.look_from = Point3d(13,2,3);
    cam.look_at   = Point3d(0,0,0);
    cam.v_up      = Vector3d(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance = 10.0;

	cam.SetScene(scene);
	cam.Render();
	cam.Save("output.png");
}

void TestSpheres()
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
	cam.image_width = 400;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.samples_per_pixel = 30;
	cam.max_bounces = 10;
	cam.verbose = true;

    cam.look_from = Vector3d(-2, 2, 1);
    cam.look_at = Vector3d(0, 0, -1);
    cam.v_up = Vector3d(0, 1, 0);
    cam.vfov = 20;

    cam.defocus_angle = 10;
    cam.focus_distance = 3.4;

	cam.SetScene(scene);
	cam.Render();
	cam.Save("output.png");
	// cam.Save("output.ppm");
}

int main() 
{
    ManySpheres();

	return 0;
}
