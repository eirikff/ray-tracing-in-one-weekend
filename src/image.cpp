#include "image.h"

namespace RayTracer
{

void GradientTestImage(std::filesystem::path filepath)
{
	Image im(256, 256);

	// Create gradient
	for (size_t x = 0; x < im.Width(); x++)
	{
		for (size_t y = 0; y < im.Height(); y++)
		{
			double r = double(x) / (im.Width() - 1);
			double g = double(y) / (im.Height() - 1);

			uint8_t ir = int(255 * r);
			uint8_t ig = int(255 * g);
			uint8_t ib = 0;

			im(x, y) = {ir, ig, ib};
		}
	}

	std::cout << "Wrote " << im.ToFile(filepath) 
			  << " bytes to " << filepath << std::endl;
}

}
