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

namespace RayTracer
{

class Image 
{
public:
	constexpr static int Depth = 3;
	using Pixel = std::array<uint8_t, Depth>;

	Image() {}
	Image(size_t width, size_t height)
	: m_width(width), m_height(height)
	{ 
		m_data.resize(height);
		for (auto &row : m_data)
		{
			row.resize(width);
			for (Pixel &channel : row)
			{
				channel.fill(0);
			}
		}
	}

	size_t Width() const { return m_width; }
	size_t Height() const { return m_height; }
	std::pair<size_t, size_t> Size() const 
	{ 
		return std::make_pair(m_width, m_height); 
	}

	Pixel& operator()(size_t x, size_t y)
	{
		return m_data[y][x];
	}
	const Pixel& operator()(size_t x, size_t y) const
	{
		return m_data[y][x];
	}

	uint8_t& operator()(size_t x, size_t y, size_t c)
	{
		return m_data[y][x][c];
	}
	const uint8_t& operator()(size_t x, size_t y, size_t c) const
	{
		return m_data[y][x][c];
	}

	std::string ToString() const 
	{
		std::stringstream ss; 

		for (size_t row = 0; row < m_height; row++)
		{
			for (size_t col = 0; col < m_width; col++)
			{
				for (size_t ch = 0; ch < Depth; ch++)
				{
					ss << std::to_string(operator()(col, row, ch));
					if (ch != Depth - 1)
					{
						ss << ",";
					}
				}
				if (col != m_width - 1)
				{
					ss << "\t";
				}
			}
			if (row != m_height - 1)
			{
				ss << "\n";
			}
		}
		ss << "\n";

		return ss.str();
	}

	std::string ToPPM() const
	{
		std::stringstream ss;
		
		ss << "P3\n" << m_width << " " << m_height << "\n255\n";
		for (size_t row = 0; row < m_height; row++)
		{
			for (size_t col = 0; col < m_width; col++)
			{
				for (size_t ch = 0; ch < Depth; ch++)
				{
					ss << std::to_string(operator()(col, row, ch)) << " ";
				}
				ss << "\n";
			}
		}

		return ss.str();
	}

	int ToFile(std::filesystem::path filepath) const 
	{
		std::ofstream out(filepath);

		if (!out) 
		{
			std::cerr << "Failed to open file '" << filepath << 
				"' for writing" << std::endl;
			return 0;
		}

		out << this->ToPPM();
		int byte_count = out.tellp();
		out.close();

		return byte_count;
	}

protected:
	size_t m_width;
	size_t m_height;

	std::vector<std::vector<Pixel>> m_data;
};

}
