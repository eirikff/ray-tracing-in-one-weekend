#pragma once

#include "interval.h"
#include "utility.h"
#include "vector3d.h"
#include <array>
#include <cstdint>


namespace RayTracer 
{

class RGB : public Vector3d
{
public:
	RGB() : Vector3d() {}
	RGB(double r, double g, double b)
	: Vector3d(r, g, b)
	{ }
	RGB(const RGB &other)
	: Vector3d(other)
	{ }
	RGB(const Vector3d &other)
	: Vector3d(other)
	{ }

	uint8_t R() const { return 255 * pixel_intensity.Clamp(m_data[0]); }
	uint8_t G() const { return 255 * pixel_intensity.Clamp(m_data[1]); }
	uint8_t B() const { return 255 * pixel_intensity.Clamp(m_data[2]); }

	RGB &operator=(const RGB &other)
	{
		if (this == &other)
			return *this;

		m_data[0] = other.x();
		m_data[1] = other.y();
		m_data[2] = other.z();

		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const RGB &c)
	{
		os << std::to_string(uint8_t(c.R())) << " " 
		   << std::to_string(uint8_t(c.G())) << " " 
		   << std::to_string(uint8_t(c.B()));
		return os;
	}

    static inline RGB Random()
    {
        return RGB{Vector3d::Random()};
    }
    static inline RGB Random(double min, double max)
    {
        return RGB{Vector3d::Random(min, max)};
    }

private:
	static const Interval pixel_intensity;
};

}
