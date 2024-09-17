#pragma once

#include <cmath>
#include <cstddef>
#include <array>
#include <ostream>

#include "utility.h"


namespace RayTracer 
{

class Vector3d;
using Point3d = Vector3d;

class Vector3d
{
public:
	Vector3d()
	: m_data{0, 0, 0}
	{ }

	Vector3d(double x, double y, double z)
	: m_data{x, y, z}
	{ }

	Vector3d(const Vector3d &other)
	: m_data{other.m_data}
	{ }

	const double &x() const { return m_data[0]; }
	const double &y() const { return m_data[1]; }
	const double &z() const { return m_data[2]; }

	const double &operator[](size_t i) const { return m_data[i]; }
	double &operator[](size_t i) { return m_data[i]; }

	Vector3d &operator=(const Vector3d &other)
	{
		if (this == &other)
			return *this;

		m_data = { other.x(), other.y(), other.z() };
		return *this;
	}
	Vector3d operator+(const Vector3d &other) const
	{
		Vector3d ret{ x() + other.x(), y() + other.y(), z() + other.z() };
		return ret;
	}
	Vector3d &operator+=(const Vector3d &other)
	{
		m_data[0] += other[0];
		m_data[1] += other[1];
		m_data[2] += other[2];
		return *this;
	}
	Vector3d operator-(void) const { return Vector3d{-x(), -y(), -z()}; }
	Vector3d operator-(const Vector3d &other) const 
	{ 
		return *this + (-other);
	}
	Vector3d &operator-=(const Vector3d &other)
	{
		m_data[0] -= other[0];
		m_data[1] -= other[1];
		m_data[2] -= other[2];
		return *this;
	}
    // Element-wise multiplication
	Vector3d operator*(const Vector3d &other) const
	{
		Vector3d ret{ x() * other.x(), y() * other.y(), z() * other.z() };
		return ret;
	}
	Vector3d operator*(double s) const
	{
		Vector3d ret{ x() * s, y() * s, z() * s };
		return ret;
	}
	friend Vector3d operator*(double s, const Vector3d &v) { return v * s; }
	Vector3d &operator*=(double s) 
	{
		m_data[0] *= s;
		m_data[1] *= s;
		m_data[2] *= s;
		return *this;
	}
	Vector3d operator/(double s) const
	{
		Vector3d ret{ x() / s, y() / s, z() / s };
		return ret;
	}
	Vector3d &operator/=(double s) 
	{
		m_data[0] /= s;
		m_data[1] /= s;
		m_data[2] /= s;
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const Vector3d &v)
	{
		os << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]";
		return os;
	}

	double dot(const Vector3d &other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z();
	}
	Vector3d cross(const Vector3d &other) const
	{
		Vector3d ret{
			y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x()
		};
		return ret;
	}

	double LengthSquared() const { return x()*x() + y()*y() + z()*z(); }
	double Length() const { return std::sqrt(LengthSquared()); }
	Vector3d Unit() const { return *this / Length(); }
    bool NearZero(double tolerance = 1e-8) const 
    { 
        return (std::fabs(x()) < tolerance)
            && (std::fabs(y()) < tolerance)
            && (std::fabs(z()) < tolerance);
    }

	static Vector3d Lerp(const Vector3d &a, const Vector3d &b, double t);   
	static Vector3d Random()
	{
		return Vector3d(Utility::random_double(), 
						Utility::random_double(),
						Utility::random_double()
		);
	}
	static Vector3d Random(double min, double max)
	{
		return Vector3d(Utility::random_double(min, max), 
						Utility::random_double(min, max),
						Utility::random_double(min, max)
		);
	}
	static Vector3d RandomUnitVector()
	{
		return Random(-1, 1).Unit();
	}
	static Vector3d RandomOnHemisphere(const Vector3d &normal)
	{
		auto unit = RandomUnitVector();
		if (unit.dot(normal) > 0.0)
		{
			return unit;
		}
		else 
		{
			return -unit;
		}
	}
    static Vector3d Reflect(const Vector3d &v, const Vector3d& n)
    {
        return v - 2 * v.dot(n) * n;
    }
    static Vector3d Refract(const Vector3d &uv, const Vector3d &n, 
                            double refraction_ratio)
    {
        double cos_theta = std::fmin(n.dot(-uv), 1.0);
        Vector3d refracted_perp = refraction_ratio * (uv + cos_theta * n);
        Vector3d refracted_parallel = -std::sqrt(
            std::fabs(1.0 - refracted_perp.LengthSquared())) * n;
        return refracted_perp + refracted_parallel;
    }



protected:
	std::array<double, 3> m_data;
};

}
