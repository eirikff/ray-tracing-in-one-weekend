#include "image.h"
#include "interval.h"
#include "stb_image_write.h"
#include <cstdint>
#include <memory>

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

const std::shared_ptr<uint8_t[]> Image::ToBuffer() const
{
	size_t size = Width() * Height() * 3;
	auto buffer = std::make_shared<uint8_t[]>(size);

	for (size_t b = 0; b < size; b++)
	{
		size_t c = b % 3;
		size_t bc = b / 3;

		size_t x = bc % m_width;
		size_t y = bc / m_width;

		buffer[b] = uint8_t(255 * (*this)(x, y, c));
	}

	return buffer;
}

int Image::SaveAsPNG(std::filesystem::path filepath) const
{
	auto buffer = ToBuffer();

	int channels = 3;
	int stride = m_width * channels;
	stbi_write_png(filepath.c_str(), m_width, m_height, channels, buffer.get(), stride);
	return 0;
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
