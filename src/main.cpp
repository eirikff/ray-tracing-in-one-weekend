#include <cstddef>

#include "camera.h"

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

	Camera cam{
		image_width, image_height, 
		viewport_width, viewport_height,
		focal_length, origin
	};
	cam.Render();
	cam.Save("output.ppm");
}

int main() 
{
	Run(400);
	return 0;
}
