#pragma once

#include <cmath>
#include <cstdlib>
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

// Returns a random real number in the range [0, 1).
inline double random_double()
{
	return std::rand() / (RAND_MAX + 1.0);
}

// Returns a random real number in the range [min, max).
inline double random_double(int min, int max)
{
	return min + (max - min) * random_double();
}

}

