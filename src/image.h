#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <array>

#include "interval.h"
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

	RGB& operator()(size_t x, size_t y)
	{
		return m_data[y][x];
	}
	const RGB& operator()(size_t x, size_t y) const
	{
		return m_data[y][x];
	}

	double& operator()(size_t x, size_t y, size_t c)
	{
		return m_data[y][x][c];
	}
	const double& operator()(size_t x, size_t y, size_t c) const
	{
		return m_data[y][x][c];
	}

	std::string ToPPM() const;
	int ToFile(std::filesystem::path filepath) const;

protected:
	size_t m_width;
	size_t m_height;

	std::vector<std::vector<RGB>> m_data;
};

}
