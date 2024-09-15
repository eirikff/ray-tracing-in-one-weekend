#pragma once

#include <cstddef>
#include <filesystem>
#include <memory>
#include <cstdint>
#include <utility>
#include <vector>

#include "color.h"


namespace RayTracer
{

class Image 
{
public:
	Image() {}
	Image(size_t width, size_t height)
	: m_width(width), m_height(height)
	{ 
		m_data.resize(height);
		for (auto &row : m_data)
		{
			row.resize(width);
		}
	}

	size_t Width() const { return m_width; }
	size_t Height() const { return m_height; }
	std::pair<size_t, size_t> Size() const 
	{ 
		return std::make_pair(m_width, m_height); 
	}

	void ApplyGamma(int gamma = 2);

	RGB& At(size_t x, size_t y) { return m_data[y][x]; }
	const RGB& At(size_t x, size_t y) const { return m_data[y][x]; }
	RGB& operator()(size_t x, size_t y) { return At(x, y); }
	const RGB& operator()(size_t x, size_t y) const { return At(x, y); }

	double& At(size_t x, size_t y, size_t c) { return m_data[y][x][c]; }
	const double& At(size_t x, size_t y, size_t c) const { return m_data[y][x][c]; }
	double& operator()(size_t x, size_t y, size_t c) { return At(x, y, c); }
	const double& operator()(size_t x, size_t y, size_t c) const { return At(x, y, c); }

	const std::shared_ptr<uint8_t[]> ToBuffer() const;

	int SaveAsPPM(std::filesystem::path filepath) const;
	int SaveAsPNG(std::filesystem::path filepath) const;

protected:
	size_t m_width;
	size_t m_height;

	std::vector<std::vector<RGB>> m_data;
};

}
