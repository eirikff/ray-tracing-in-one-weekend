#pragma once

#include <cmath>
#include <limits>


namespace RayTracer::Constants
{

constexpr double Infinity = std::numeric_limits<double>::infinity();
constexpr double Pi = 3.1415926535897932385;

}

namespace RayTracer::Utility
{

inline double deg2rad(double degrees)
{
	return degrees * Constants::Pi / 180.0;
}

}

