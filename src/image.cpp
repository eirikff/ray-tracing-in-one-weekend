#include "image.h"
#include <string>

namespace RayTracer
{

int Image::SaveAsPPM(std::filesystem::path filepath) const 
{
	std::ofstream out(filepath);

	if (!out) 
	{
		std::cerr << "Failed to open file '" << filepath << 
			"' for writing" << std::endl;
		return 0;
	}

	out << "P3\n" << m_width << " " << m_height << "\n255\n";
	for (size_t row = 0; row < m_height; row++)
	{
		for (size_t col = 0; col < m_width; col++)
		{
			out << (*this)(col, row) << "\n";
		}
	}

	int byte_count = out.tellp();
	out.close();

	return byte_count;
}

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
			im(x, y) = RGB{r, g, 0};
		}
	}

	std::cout << "Wrote " << im.SaveAsPPM(filepath) 
			  << " bytes to " << filepath << std::endl;
}

}
